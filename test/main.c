/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:11:49 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 06:18:42 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIGNAL_NONE    0
#define SIGNAL_SIGINT  1
#define SIGNAL_SIGQUIT 2

volatile sig_atomic_t g_received_signal = 0;

void	handle_signal(int signo)
{
	if (signo == SIGINT)
		g_received_signal = SIGNAL_SIGINT;
	else if (signo == SIGQUIT)
		g_received_signal = SIGNAL_SIGQUIT;
}

void	setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(void)
{
	char *line;

	setup_signals();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
        if (g_received_signal == SIGNAL_SIGINT)
        {
            write(1, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
            g_received_signal = SIGNAL_NONE;
            free(line);
            continue;
        }
		if (*line)
			add_history(line);
		printf("%s\n", line);
        free(line);
	}
}


