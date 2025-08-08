/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:47:39 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_unset(t_minishell *minishell, t_script *script)
{
	int	i;

	i = 1;
	while (script->cmd_args[i])
	{
		if (unset_env(script->cmd_args[i], &(minishell->m_env)))
			return (1);
		else if (unset_env(script->cmd_args[i], &(minishell->s_env)))
		{
		}
		i++;
	}
	return (0);
}
