/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 06:10:57 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 06:11:56 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
