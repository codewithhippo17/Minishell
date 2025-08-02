/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/31 04:25:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;

	setup_shell_signals();
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$ ");
		if (minishell->input == NULL)
			free_exit_minishell(minishell, EXIT_SUCCESS);
		if (g_received_signal == SIGNAL_SIGINT)
		{
			g_received_signal = SIGNAL_NONE;
			minishell->status = 130;
		}
		if (*(minishell->input) == '\0')
		{
			free(minishell->input);
			continue ;
		}
		add_history(minishell->input);
		minishell->script = ft_parrsing(minishell);
		extract_args(minishell);
		if (minishell->script)
			handle_command(minishell);
		free(minishell->input);
	}
	restore_shell_signals();
	free(minishell);
	return (EXIT_SUCCESS);
}

/* 		print_script(minishell->script);
		printf("--------°°--exec--out--bellow--°°---------\n"); */
