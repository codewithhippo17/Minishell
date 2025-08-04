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

int	exec_unset(t_minishell *minishell)
{
	int	i;

	i = 1;
	while (minishell->script->cmd_args[i])
	{
		if (unset_env(minishell->script->cmd_args[i], &(minishell->m_env)))
			return (1);
		i++;
	}
	return (0);
}
