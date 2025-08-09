/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/09 18:56:12 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/chardefs.h>

int	exec_unset(t_minishell *minishell, t_script *script)
{
	int	i;

	i = 1;
	while (script->cmd_args[i])
	{
		minishell->status = unset_env(script->cmd_args[i], &(minishell->m_env));
		if (minishell->status == 0)
			minishell->status = unset_env(script->cmd_args[i],
					&(minishell->s_env));
		i++;
	}
	return (0);
}
