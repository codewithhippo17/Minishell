/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:36:57 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:37:06 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	run_heredoc_child(t_heredoc *hd, t_minishell *minishell)
{
	setup_child_signals();
	while (1)
	{
		hd->line = readline("> ");
		collector_register(hd->line, SCOPE_CHILD);
		if (!hd->line || (hd->line && ft_strcmp(hd->line, hd->del) == 0))
			break ;
		if (hd->quote == NQS)
		{
			expander(&(hd->line), minishell);
		}
		write(hd->tmp_fd, hd->line, ft_strlen(hd->line));
		write(hd->tmp_fd, "\n", 1);
	}
	close(hd->tmp_fd);
	close(hd->fd);
	cleanup_exit(0);
}

static int	run_heredoc_parent(t_heredoc *hd)
{
	waitpid(hd->pid, &hd->status, 0);
	if (WIFEXITED(hd->status))
		return (WEXITSTATUS(hd->status));
	else if (WIFSIGNALED(hd->status))
		return (128 + WTERMSIG(hd->status));
	return (0);
}

int	heredoc(t_heredoc *hd, t_minishell *minishell)
{
	hd->tmp_fd = open(hd->filename, O_CREAT | O_WRONLY, 0600);
	if (hd->tmp_fd == -1)
		return (1);
	hd->fd = open(hd->filename, O_RDONLY, 0600);
	if (hd->fd == -1)
		return (close(hd->tmp_fd), 1);
	unlink(hd->filename);
	hd->pid = fork();
	if (hd->pid < 0)
		return (perror("fork"), 1);
	if (hd->pid == 0)
		run_heredoc_child(hd, minishell);
	else
	{
		signal(SIGINT, SIG_IGN);
		minishell->status = run_heredoc_parent(hd);
		if (minishell->status == 130 || minishell->status == 131)
		{
			setup_shell_signals();
			ft_putstr_fd(HEREDOC_ERROR, 2);
			return (close(hd->fd), close(hd->tmp_fd), minishell->status = 130, 1);
		}
		setup_shell_signals();
	}
	return (close(hd->tmp_fd), minishell->status);
}
