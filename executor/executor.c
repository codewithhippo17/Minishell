/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 06:10:57 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 06:59:21 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcule_cmd(t_script *script)
{
	int			i;
	t_script	*current;

	i = 0;
	current = script;
	while (current)
	{
		i++;
		current = current->next_cmd;
	}
	return (i);
}

void	handle_command(t_minishell *minishell)
{
	if (is_builtin(minishell->script->cmd_args))
		execute_builtin(minishell, minishell->script);
	else
	    minishell->status = pipex(calcule_cmd(minishell->script), minishell);
}
