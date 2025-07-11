/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:35 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/07 18:22:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	handle_command(t_minishell *minishell)
{
	if (is_piped(minishell->input))
		printf("%s\n", minishell->input);
	else
	{
		if (is_builtin(minishell->cmd_args))
			execute_builtin(minishell);
		else
			minishell->status = ft_exec_all(minishell);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$");
		add_history(minishell->input);
		if (minishell->input == NULL)
			free_exit_minishell(minishell, EXIT_SUCCESS);
		minishell->cmd_args = ft_split(minishell->input, ' ');
		if (!minishell->cmd_args)
			free_exit_minishell(minishell, EXIT_FAILURE);
		else if (minishell->cmd_args[0])
			handle_command(minishell);
		printf("%d\n", minishell->status);
		free(minishell->input);
		free_strings(minishell->cmd_args);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}
