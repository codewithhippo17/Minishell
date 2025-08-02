/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:30:59 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/01 01:57:19 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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

void	setup_shell_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &g_old_sigint);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, &g_old_sigquit);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
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
