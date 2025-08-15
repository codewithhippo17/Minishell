/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/09 18:45:26 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dispatch(t_minishell *minishell)
{
	minishell->script = ft_parrsing(minishell);
	if (!minishell->script)
	{
		free(minishell->input);
		return ;
	}
	collector_cleanup(SCOPE_TEMP);
	extract_args(minishell);
	handle_command(minishell);
	collector_cleanup(SCOPE_TEMP);
	collector_cleanup(SCOPE_SESSION);
	free(minishell->input);
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;

	minishell = NULL;
	setup_shell_signals();
	collector_init_shell(&minishell, env);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$ ");
		if (minishell->input == NULL)
			cleanup_exit(0);
		if (g_received_signal == SIGNAL_SIGINT)
		{
			g_received_signal = SIGNAL_NONE;
			minishell->status = 130;
		}
		if (*(minishell->input) == '\0')
		{
			free(minishell->input);
			collector_cleanup(SCOPE_SESSION);
			continue ;
		}
		add_history(minishell->input);
		dispatch(minishell);
	}
}
