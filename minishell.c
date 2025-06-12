/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:15:35 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <string.h>

int	is_builtin(char **s)
{
	if (ft_strncmp(s[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "env", ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "export", ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int	is_piped(char *input)
{
	if (ft_strchr(input, '|'))
		return (1);
	return (0);
}

void	handle_command(t_minishell *minishell)
{
	if (is_piped(minishell->input))
		pipex(minishell);
	else
	{
		if (is_builtin(minishell->cmd_args))
			execute_builtin(minishell);
		else
			minishell->status = ft_exec_all(minishell);
	}
}

char	**set_env(char **env, int flag)
{
	int		i;
	int		l;
	char	**my_env;

	i = 0;
	l = 0;
	while (env[l])
		l++;
	my_env = malloc((l + 1) * sizeof(char *));
	if (!my_env)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		free_split(my_env);
		return (NULL);
	}
	while (i < l)
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			ft_putstr_fd("Memory allocation failed\n", 2);
			free_split(my_env);
			return (NULL);
		}
		i++;
	}
	my_env[i] = NULL;
	if (flag)
	{
		free(my_env[i - 1]);
		my_env[i - 1] = NULL;
	}
	return (my_env);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!(minishell->m_env = set_env(env, 0)))
		return (EXIT_FAILURE);
	if (!(minishell->s_env = set_env(env, 1)))
		return (EXIT_FAILURE);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$");
		add_history(minishell->input);
		if (minishell->input == NULL)
		{
			free_split(minishell->m_env);
			free_split(minishell->s_env);
			free(minishell->input);
			free(minishell);
			exit(EXIT_SUCCESS);
		}
		minishell->cmd_args = ft_split(minishell->input, ' ');
		if (!minishell->cmd_args)
		{
			free_split(minishell->m_env);
			free_split(minishell->s_env);
			free(minishell->input);
			free(minishell);
			return (EXIT_FAILURE);
		}
		else if (minishell->cmd_args[0])
		{
			handle_command(minishell);
		}
		printf("%d\n", minishell->status);
		free(minishell->input);
		free_split(minishell->cmd_args);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}
