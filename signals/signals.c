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


volatile sig_atomic_t g_received_signal = 0;

static struct sigaction g_old_sigint;
static struct sigaction g_old_sigquit;

void handle_signal(int signo)
{
    if (signo == SIGINT)
        g_received_signal = SIGNAL_SIGINT;
    else if (signo == SIGQUIT)
        g_received_signal = SIGNAL_SIGQUIT;
}

// TODO: call it in shell startup

void setup_shell_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &handle_signal;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, &g_old_sigint);

    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, &g_old_sigquit);
}

// TODO: call it in after fork before execve

void setup_child_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = SIG_DFL;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}

// TODO: call it in shell shut down and exit

void restore_shell_signals(void)
{
    sigaction(SIGINT, &g_old_sigint, NULL);
    sigaction(SIGQUIT, &g_old_sigquit, NULL);
}
