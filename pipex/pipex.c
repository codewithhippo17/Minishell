/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:21:45 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:48:48 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*error_managment(t_minishell *minishell, t_script *script, char **args)
{
	char		*path;
	struct stat	stats;

	if (!args || !args[0] || ft_strchr(args[0], '/'))
	{
		stat(args[0], &stats);
		if (access(args[0], F_OK) == -1)
			printerror(script, args, ": No such file or directory\n", 127);
		else if (S_ISDIR(stats.st_mode))
			printerror(script, args, ": Is a directory\n", 126);
		path = ft_strdup(args[0], SCOPE_SESSION);
	}
	else
	{
		path = get_path(args[0], minishell->m_env);
		if (!path)
			printerror(script, args, ": command not found\n", 127);
		else
		{
			stat(path, &stats);
			if (S_ISDIR(stats.st_mode))
				printerror(script, args, ": Is a directory\n", 126);
		}
	}
	return (path);
}

static void	extrenal_cmds(t_minishell *minishell, t_script *script, char **args)
{
	char	*path;

	path = error_managment(minishell, script, args);
	execve(path, args, minishell->m_env);
	if (access(path, X_OK) == -1)
		printerror(script, args, ": Permission denied\n", 126);
	else
		printerror(script, args, ": Eexc format error\n", EXIT_FAILURE);
}

static void	child_pr_all(t_minishell *minishell, t_script *script)
{
	t_builtin_name	name;

	name = which_bultin(*script->cmd_args);
	if (name != UNKNOWN)
	{
		execute_builtin(minishell, script, name);
		cleanup_exit(minishell->status);
	}
	else
	{
		if (script->red)
		{
			if (redirection(script))
				cleanup_exit(1);
		}
		extrenal_cmds(minishell, script, script->cmd_args);
	}
}

int	pipex(int ac, t_minishell *minishell)
{
	// Ignore SIGINT and SIGQUIT in parent while running children
	setup_ignore_signals();
	pid_t		*pids;
	t_script	*curent;

	int p = -1, i = -1, fd[2];
	pids = my_alloc(sizeof(int) * ac, SCOPE_SESSION);
	curent = minishell->script;
	while (curent)
	{
		if (curent->next_cmd && pipe(fd) == -1)
			ft_perror("pipe", 1);
		pids[++i] = fork();
		if (pids[i] == -1)
			return (perror("fork"), 1);
		if (pids[i] == 0)
		{
						/* Set up child signal handlers */
			setup_child_signals();
			setup_input(p);
			setup_output(fd, i, ac);
			child_pr_all(minishell, curent);
		}
		close_pr_fds(curent, &p, fd);
		curent = curent->next_cmd;
	}
	if (p != -1)
		close(p);
	int ret = wait_for_children(pids, ac);
	restore_shell_signals();
	return (ret);
}
