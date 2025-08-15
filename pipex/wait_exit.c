/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:06:55 by ybelghad			#+#    #+#            */
/*   Updated: 2025/08/07 15:33:35 by ybelghad		   ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *str, int ex_st)
{
	perror(str);
	exit(ex_st);
}

void	printerror(t_script *script, char **args, char *err, int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(err, 2);
	if (script->red)
		restore_fds(script);
	cleanup_exit(exinum);
}

static int	setup_signal(int status)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(2, "\n", 1);
		setup_shell_signals();
		return (130);
	}
	else if (WTERMSIG(status) == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		setup_shell_signals();
		return (131);
	}
	return (0);
}

int	wait_for_children(int *pid, int ac)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	status = 0;
	exit_status = 0;
	signal(SIGINT, SIG_IGN);
	while (i < ac)
	{
		waitpid(pid[i], &status, 0);
		if (WIFSIGNALED(status))
			return (setup_signal(status));
		else
			exit_status = WEXITSTATUS(status);
		i++;
	}
	setup_shell_signals();
	return (exit_status);
}
