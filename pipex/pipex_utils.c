/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:46:05 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/21 02:50:17 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	ft_perror(char *str, int ex_st)
{
	perror(str);
	exit(ex_st);
}

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

int	wait_for_children(int *pid, int ac)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	status = 0;
	exit_status = 0;
	while (i < ac)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		i++;
	}
	return (exit_status);
}
