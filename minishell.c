/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 04:46:40 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcule_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

t_minishell	*shell(t_minishell *mini)
{
	int			i;
	char		**cmd;
	t_minishell	*curent;

	i = 0;
	cmd = ft_split(mini->input, '|');
	if (!cmd)
	{
		free_strings(mini->cmd_args);
		free_exit_minishell(mini, 1);
	}
	curent = mini;
	while (cmd[i])
	{
		curent->cmd_args = ft_split(cmd[i], ' ');
		curent->red = NULL;
		curent->next = malloc(sizeof(t_minishell));
		curent = curent->next;
		i++;
	}
	free_strings(cmd);
	return (mini);
}

void	handle_pipe(t_minishell *mini)
{
	char	**cmd;
	int		n_cmd;

	mini = shell(mini);
	if (!mini)
	{
		free_strings(mini->cmd_args);
		free_exit_minishell(mini, 1);
	}
	cmd = ft_split(mini->input, '|');
	if (!cmd)
	{
		free_strings(mini->cmd_args);
		free_exit_minishell(mini, 1);
	}
	n_cmd = calcule_cmd(cmd);
	free_strings(cmd);
	mini->status = pipex(n_cmd, mini);
}

void	handle_command(t_minishell *minishell)
{
	if (is_piped(minishell->input))
		handle_pipe(minishell);
	else
	{
		if (is_builtin(minishell->cmd_args))
			execute_builtin(minishell);
		else
			minishell->status = ft_exec_all(minishell);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
	// t_token		*token;

	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$ ");
		add_history(minishell->input);
		if (minishell->input == NULL)
			free_exit_minishell(minishell, EXIT_SUCCESS);
		minishell->cmd_args = ft_split(minishell->input, ' ');
		// token = token_init();
		// mini_update(minishell, token);
		// minishell->red = red_init();
		if (!minishell->cmd_args)
			free_exit_minishell(minishell, EXIT_FAILURE);
		else if (minishell->cmd_args[0])
			handle_command(minishell);
    // char *str = my_getenv("dd", minishell->m_env);
    // char *str1 = getenv("d");
    // char *str2 = my_getenv("ff", minishell->m_env);
    // char *str3 = getenv("f");
    // printf("%d\n", is_var(minishell->cmd_args[1]));
		printf("%d\n", minishell->status);
		free(minishell->input);
		free_strings(minishell->cmd_args);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}
