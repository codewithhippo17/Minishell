/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 00:21:45 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/21 02:48:52 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerror(t_minishell *mini, char **args, char *err, int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(err, 2);
	free_strings(mini->cmd_args);
	free_exit_minishell(mini, exinum);
}

static void	child_pr_all(t_minishell *mini, char **args)
{
	char		*path;
	struct stat	stats;

	if (ft_strchr(args[0], '/'))
	{
		stat(args[0], &stats);
		if (access(args[0], F_OK) == -1)
			printerror(mini, args, ": No such file or directory\n", 127);
		else if (access(args[0], X_OK) == -1)
			printerror(mini, args, ": Permission denied\n", 126);
		else if (S_ISDIR(stats.st_mode))
			printerror(mini, args, ": Is a directory\n", 126);
		path = ft_strdup(args[0]);
	}
	else
	{
		path = get_path(args[0], mini->m_env);
		if (!path)
			printerror(mini, args, ": command not found\n", 127);
	}
	execve(path, args, mini->m_env);
	free(path);
	printerror(mini, args, ": Failed to execve\n", 127);
}

int	pipex(int ac, t_minishell *mini)
{
	int		exit_status;
	pid_t	pids[ac];
	t_minishell	*curent;

	int(p), (i), (fd[2]);
	p = -1;
	i = 0;
	curent = mini;
	while (i < ac)
	{
		if (pipe(fd) == -1)
			ft_perror("pipe", 1);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			setup_input(p);
			setup_output(fd, i, ac);
			child_pr_all(mini, curent->cmd_args);
		}
		if (p != -1)
			close(p);
		p = fd[0];
		close(fd[1]);
		curent = curent->next;
		i++;
	}
	close(p);
	exit_status = wait_for_children(pids, ac);
	return (exit_status);
}
