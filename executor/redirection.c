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

int	save_fds(t_red *red)
{
	red->saved_stdin = dup(0);
	red->saved_stdout = dup(1);
	if (red->saved_stdin == -1 || red->saved_stdout == -1)
		return (1);
	return (0);
}

void	restore_fds(t_red *red)
{
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
}

int	apply_redirection(t_red *current)
{
	if (current->type == LR)
		current->fd = open(current->path, O_RDONLY);
	else if (current->type == RR)
		current->fd = open(current->path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (current->type == DRR)
		current->fd = open(current->path, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (current->fd == -1)
	{
    perror(strerror(errno));
    return (1);
  }
	return (0);
}

void	redirect_io(t_red *current)
{
	if (current->type == LR || current->type == HEREDOC)
		dup2(current->fd, 0);
	else
		dup2(current->fd, 1);
	close(current->fd);
}

int	redirection(t_red *red)
{
	t_red	*current;

	current = red;
	if (save_fds(red) == -1)
		return (1);
	while (current)
	{
		if (apply_redirection(current) == 1)
			return (1);
		redirect_io(current);
		current = current->next;
	}
	return (0);
}
