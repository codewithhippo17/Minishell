/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:53:32 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:53:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_exit(char *error, int status)
{
	perror(error);
	exit(status);
}

void	ft_free_exit(char **args, char *erno, int status)
{
	ft_free_tab(args);
	perror(erno);
	exit(status);
}

void	ft_close_wait_exit(int p_fd[], int pid1, int pid2)
{
	int	status;

	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	exit(WEXITSTATUS(status));
}
