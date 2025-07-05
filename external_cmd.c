/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:19 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:14:19 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	child_pr_all(t_minishell *mini)
{
	char	*path;

	path = get_path(mini->cmd_args[0], mini->m_env);
	execve(path, mini->cmd_args, mini->m_env);
	free_split(mini->cmd_args);
	free_split(mini->m_env);
	free_split(mini->s_env);
  free(mini);
	exit(127);
}

int	ft_exec_all(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		ft_exit("fork: Error\n");
	if (pid == 0)
		child_pr_all(minishell);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (status);
}
