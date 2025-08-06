/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <ybelghad@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:22:44 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:46:50 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(t_minishell *m, t_script *s)
{
	return (exec_export(m, s));
}

int	builtin_unset(t_minishell *m, t_script *s)
{
	return (exec_unset(m, s));
}

int	builtin_exit(t_minishell *m, t_script *s)
{
    (void)m;
	return (ft_my_exit(s));
}

int	builtin_unknown(t_minishell *m, t_script *s)
{
	(void)s;
	(void)m;
	return (1);
}
