/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 06:10:57 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/02 16:47:35 by ybelghad         ###   ########.fr       */
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
	t_builtin_name	name;

	name = which_bultin(*minishell->script->cmd_args);
	if (name != UNKNOWN && !minishell->script->next_cmd)
		execute_builtin(minishell, minishell->script, name);
	else if (minishell->script->cmd_args)
		minishell->status = pipex(calcule_cmd(minishell->script), minishell);
	else
	{
		minishell->status = redirection(minishell->script);
		if (minishell->status)
			return ;
		minishell->status = restore_fds(minishell->script);
		if (minishell->status)
			return ;
	}
}
