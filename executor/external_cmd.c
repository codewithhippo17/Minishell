/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:19 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 01:48:49 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static void	printerror(t_minishell *minishell, char *err, int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(minishell->script->cmd_args[0], 2);
	ft_putstr_fd(err, 2);
	free_strings(minishell->script->cmd_args);
	free_exit_minishell(minishell, exinum);
	exit(exinum);
}

static void	child_pr_all(t_minishell *minishell)
{
	char		*path;
	struct stat	stats;

	if (ft_strchr(minishell->script->cmd_args[0], '/'))
	{
		stat(minishell->script->cmd_args[0], &stats);
		if (access(minishell->script->cmd_args[0], F_OK) == -1)
			printerror(minishell, ": No such file or directory\n", 127);
		else if (S_ISDIR(stats.st_mode))
			printerror(minishell, ": Is a directory\n", 126);
		path = ft_strdup(minishell->script->cmd_args[0]);
	}
	else
	{
		path = get_path(minishell->script->cmd_args[0], minishell->m_env);
    stat(path, &stats);
    if (S_ISDIR(stats.st_mode))
      printerror(minishell, ": Is a directory\n", 126);
		if (!path)
			printerror(minishell, ": command not found\n", 127);
	}
	if (minishell->script->red)
	{
		if (redirection(minishell->script->red) == 1)
			exit(1);
	}
	execve(path, minishell->script->cmd_args, minishell->m_env);
	free(path);
	printerror(minishell, ": Permission denied\n", 126);
}

int	ft_exec_all(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	int		exit_status;

  status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_exit_minishell(minishell, 1);
	}
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
