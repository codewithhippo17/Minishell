/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:06:55 by ybelghad	       #+#    #+#             */
/*   Updated: 2025/08/01 12:06:55 by ybelghad  	      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *str, int ex_st)
{
	perror(str);
	exit(ex_st);
}

void	printerror(t_minishell *minishell, char **args, char *err,
		int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(err, 2);
	free_strings(minishell->script->cmd_args);
	free_exit_minishell(minishell, exinum);
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
