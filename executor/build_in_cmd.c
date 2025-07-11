/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/06 19:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var(char *str)
{
	int	i;

	if (!str || !*str)
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (2);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (2);
		i++;
	}
	if (str[i] == '=')
		return (0);
	return (1);
}

int	handle_export_arg(t_minishell *minishell, int i)
{
	int	status;
	int	valid_var;

	status = 0;
	valid_var = is_var(minishell->cmd_args[i]);
	if (valid_var == 0)
	{
		status = exports(minishell->cmd_args[i], &(minishell->s_env));
		if (status == 0)
			status = exports(minishell->cmd_args[i], &(minishell->m_env));
	}
	else if (valid_var == 1)
		status = exports(minishell->cmd_args[i], &(minishell->s_env));
	else
		status = 1;
	if (status != 0)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(minishell->cmd_args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (status);
}

int	declair_x(char **env)
{
	int		i;
	int		j;
	int		l;
	char	*temp;
	char	**split;

	i = 0;
	l = 0;
	while (env[l])
		l++;
	while (i < l)
	{
		j = 0;
		while (j < l - 1)
		{
			if (ft_strcmp(env[i], env[j]) < 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		j = 1;
		split = ft_split(env[i], '=');
		if (!split)
			return (1);
		printf("declare -x %s=\"", split[0]);
		while (split[j])
		{
			printf("%s", split[j]);
			if (split[j + 1])
				printf("=");
			j++;
		}
		printf("\"\n");
		free_strings(split);
		split = NULL;
		i++;
	}
	return (0);
}

int	exec_export(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (minishell->cmd_args[i])
	{
		while (minishell->cmd_args[i])
		{
			status = handle_export_arg(minishell, i);
			i++;
		}
	}
	else
	{
		status = declair_x(minishell->s_env);
	}
	return (status);
}

int	exec_unset(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (minishell->cmd_args[i])
	{
		status = unset_env(minishell->cmd_args[i], &(minishell->m_env));
		if (!status)
			status = unset_env(minishell->cmd_args[i], &(minishell->s_env));
		else
			return (1);
		i++;
	}
	return (status);
}

void	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "echo",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = echo(minishell->input, minishell->status);
	else if (ft_strncmp(minishell->cmd_args[0], "cd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = cd(minishell->cmd_args[1], minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd",
			ft_strlen(minishell->cmd_args[0])) == 0 && !minishell->cmd_args[1])
		minishell->status = pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "env",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = envierment(minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = exec_export(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "unset",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = exec_unset(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "exit",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = ft_my_exit(minishell);
}
