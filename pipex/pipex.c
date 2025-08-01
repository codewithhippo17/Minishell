/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:21:45 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/31 04:23:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerror(t_minishell *minishell, char **args, char *err,
		int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(err, 2);
	free_strings(minishell->script->cmd_args);
	free_exit_minishell(minishell, exinum);
}

static void	child_pr_all(t_minishell *minishell, t_script *script, char **args)
{
	char		*path;
	struct stat	stats;

	if (ft_strchr(args[0], '/'))
	{
		stat(args[0], &stats);
		if (access(args[0], F_OK) == -1)
			printerror(minishell, args, ": No such file or directory\n", 127);
		else if (access(args[0], X_OK) == -1)
			printerror(minishell, args, ": Permission denied\n", 126);
		else if (S_ISDIR(stats.st_mode))
			printerror(minishell, args, ": Is a directory\n", 126);
		path = ft_strdup(args[0]);
	}
	else
	{
		path = get_path(args[0], minishell->m_env);
		if (!path)
			printerror(minishell, args, ": command not found\n", 127);
	}
	if (script->red)
	{
		if (redirection(script->red) == 1)
			exit(1);
	}
	execve(path, args, minishell->m_env);
	free(path);
	printerror(minishell, args, ": Failed to execve\n", 127);
}

int	pipex(int ac, t_minishell *minishell)
{
	pid_t		*pids;
	t_script	*curent;

	int(p), (i), (fd[2]);
	p = -1;
	i = -1;
	pids = malloc(sizeof(int) * ac);
	curent = minishell->script;
	while (curent)
	{
		if (curent->next_cmd && pipe(fd) == -1)
			ft_perror("pipe", 1);
		pids[++i] = fork();
		if (pids[i] == 0)
		{
            /*  * NOTE: here signals logic
                *
                *
                *
                *
                */
			setup_input(p);
			setup_output(fd, i, ac);
			if (is_builtin(curent->cmd_args))
			{
				execute_builtin(minishell, curent);
				exit(minishell->status);
			}
			else
				child_pr_all(minishell, curent, curent->cmd_args);
		}
		if (p != -1)
			close(p);
		p = fd[0];
		close(fd[1]);
		curent = curent->next_cmd;
	}
	return (close(p), wait_for_children(pids, ac));
}
