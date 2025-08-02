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
	(void)s;
	return (exec_export(m));
}

int	builtin_unset(t_minishell *m, t_script *s)
{
	(void)s;
	return (exec_unset(m));
}

int	builtin_exit(t_minishell *m, t_script *s)
{
	(void)s;
	return (ft_my_exit(m));
}

int	builtin_unknown(t_minishell *m, t_script *s)
{
	(void)s;
	(void)m;
	return (1);
}
