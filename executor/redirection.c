/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:56:33 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:47:32 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_abg(t_red *red)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(red->path, 2);
	ft_putstr_fd(": ambiguous redirect", 2);
}

int	save_fds(t_script *script)
{
	if (!script)
		return (1);
	script->saved_stdin = dup(0);
	script->saved_stdout = dup(1);
	if (script->saved_stdin == -1 || script->saved_stdout == -1)
		return (1);
	return (0);
}

int	restore_fds(t_script *script)
{
	if (!script)
		return (1);
	if (script->saved_stdin != -1)
	{
		dup2(script->saved_stdin, 0);
		close(script->saved_stdin);
		script->saved_stdin = -1;
	}
	if (script->saved_stdout != -1)
	{
		dup2(script->saved_stdout, 1);
		close(script->saved_stdout);
		script->saved_stdout = -1;
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
		perror(red->path);
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
	}
	else if (dup2(red->fd, 1) == -1)
		return (1);
	close(red->fd);
	return (0);
}


int	redirection(t_script *script)
{
	t_red	*current;

	current = script->red;
	script->saved_stdin = -1;
	script->saved_stdout = -1;
	if (save_fds(script) == 1)
		return (1);
	while (current)
	{
		if (current->ambg == AMBG)
		{
			restore_fds(script);
			print_abg(current);
			return (1);
		}
		if (apply_redirection(current))
		{
			restore_fds(script);
			return (1);
		}
		if (redirect_io(current))
		{
			restore_fds(script);
			return (1);
		}
		current = current->next;
	}

	return (0);
}
