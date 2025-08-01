/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:22:34 by marvin            #+#    #+#             */
/*   Updated: 2025/08/01 14:22:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_echo(t_minishell *m, t_script *s)
{
	(void)m;
	return (echo(s->cmd_args));
}

int	builtin_cd(t_minishell *m, t_script *s)
{
	return (cd(s->cmd_args, m));
}

int	builtin_pwd(t_minishell *m, t_script *s)
{
	(void)m;
	(void)s;
	return (pwd());
}

int	builtin_env(t_minishell *m, t_script *s)
{
	(void)s;
	return (envierment(m->m_env));
}
