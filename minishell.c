/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 06:11:27 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "includes/ast.h"

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

	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
  	signal(SIGINT, handle_main_signal);
	signal(SIGQUIT, SIG_IGN);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$ ");
    if (minishell->input == NULL)
			free_exit_minishell(minishell, EXIT_SUCCESS);
    if (*(minishell->input) == '\0')
    {
      printf("%d\n", minishell->status);
      continue;
    }
		add_history(minishell->input);

    minishell->script = ft_parrsing(minishell);
    if (g_signal_received == SIGINT)
		{
			free(minishell->input);
			continue ; 
		}
    extract_args(minishell);
    handle_command(minishell);
		printf("\n%d\n", minishell->status);
    free(minishell->input);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}
