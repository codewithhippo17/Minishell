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

#include "../minishell.h"

// This is the ONLY global variable allowed
int		g_signal_received = 0;

void	handle_main_signal(int sig)
{
	g_signal_received = sig; // Only store the signal number
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}



int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
	char		*input;
	t_token     *tokens;
    int nb = 0;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
	signal(SIGINT, handle_main_signal);
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ in interactive mode
	while (argc == 1 && argv)
	{
        nb = 0;
		g_signal_received = 0; // Reset signal flag
		input = readline("minishell$> ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			free(input);
			continue ; // Go to next prompt
		}
	}
	return (EXIT_SUCCESS);
}


