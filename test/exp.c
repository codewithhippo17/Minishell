/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:10:57 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/15 11:11:14 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
	char		*str;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
    str = my_getenv("i", minishell->m_env);
	printf("a%sb\n", str);
	free(minishell);
	return (EXIT_SUCCESS);
}
