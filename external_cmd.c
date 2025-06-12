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

static void	child_pr_all(char **cmd, char **env)
{
	char	*path;

	path = get_path(cmd[0], env);
	execve(path, cmd, env);
	free_split(cmd);
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
		child_pr_all(minishell->cmd_args, minishell->m_env);
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
