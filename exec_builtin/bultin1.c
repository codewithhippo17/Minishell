/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <ybelghad@student.1337.ma           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:22:34 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:45:49 by ybelghad         ###   ########.fr       */
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
