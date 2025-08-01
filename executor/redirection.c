/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:56:33 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/31 04:37:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/types.h>

int	save_fds(t_red *red)
{
	if (!red)
		return (1);
	red->saved_stdin = dup(0);
	red->saved_stdout = dup(1);
	if (red->saved_stdin == -1 || red->saved_stdout == -1)
		return (1);
	return (0);
}

int	restore_fds(t_red *red)
{
	if (!red)
		return (1);
	if (red->saved_stdin != -1)
	{
		dup2(red->saved_stdin, 0);
		close(red->saved_stdin);
		red->saved_stdin = -1;
	}
	if (red->saved_stdout != -1)
	{
		dup2(red->saved_stdout, 1);
		close(red->saved_stdout);
		red->saved_stdout = -1;
	}
	return (0);
}

int	apply_redirection(t_red *red)
{
	if (!red)
		return (1);
	if (red->type == LR)
		red->fd = open(red->path, O_RDONLY);
	else if (red->type == RR)
		red->fd = open(red->path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (red->type == DRR)
		red->fd = open(red->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (red->fd == -1)
	{
		perror(strerror(errno));
		return (1);
	}
	return (0);
}

int	redirect_io(t_red *red)
{
	if (!red)
		return (1);
	if (red->type == LR || red->type == HEREDOC)
	{
		if (dup2(red->fd, 0) == -1)
			return (1);
		else if (dup2(red->fd, 1) == -1)
			return (1);
	}
	close(red->fd);
	return (0);
}

int	redirection(t_red *red)
{
	t_red	*current;

	current = red;

	if (save_fds(red) == 1)
		return (1);
	while (current)
	{
		if (apply_redirection(current))
		{
			restore_fds(current);
			return (1);
		}
		if (redirect_io(current))
		{
			restore_fds(current);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
