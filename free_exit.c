/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:23 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:14:23 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		free(s[j]);
		j++;
	}
	free(s);
}

void	ft_exit(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

void	ft_exit_status(char *error, int status)
{
	perror(error);
	exit(status);
}

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
