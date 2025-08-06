/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipex_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:46:05 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:48:43 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"
#include <unistd.h>

void	setup_input(int p)
{
	if (p != -1)
	{
		dup2(p, 0);
		close(p);
	}
}

void	setup_output(int *fd, int i, int ac)
{
	if (i < ac - 1)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
	}
}

void	close_pr_fds(t_script *script, int *p, int *fd)
{
	if (script->red && script->red->type == HEREDOC)
		close(script->red->fd);
	if (*p != -1)
		close(*p);
	if (script->next_cmd)
	{
		close(fd[1]);
		*p = fd[0];
	}
	else
		*p = -1;
}
