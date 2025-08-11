/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:30:59 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 19:11:53 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <unistd.h>

sig_atomic_t			g_received_signal = 0;

static struct sigaction	g_old_sigint;
static struct sigaction	g_old_sigquit;

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		g_received_signal = SIGNAL_SIGINT;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
		g_received_signal = SIGNAL_SIGQUIT;
}

void	handle_child_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_received_signal = 130;
		cleanup_exit(130);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\n", 1);
		g_received_signal = 131;
		cleanup_exit(131);
	}
}

void	setup_shell_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = &handle_signal;
	sa_int.sa_flags = SA_RESTART;
	sigemptyset(&sa_int.sa_mask);
	sigaction(SIGINT, &sa_int, &g_old_sigint);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigemptyset(&sa_quit.sa_mask);
	sigaction(SIGQUIT, &sa_quit, &g_old_sigquit);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_child_sig;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	restore_shell_signals(void)
{
	sigaction(SIGINT, &g_old_sigint, NULL);
	sigaction(SIGQUIT, &g_old_sigquit, NULL);
}
