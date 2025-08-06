/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:10:42 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:10:42 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envierment(char **m_env)
{
	int	i;

	i = 0;
	while (m_env[i])
	{
		if (ft_strchr(m_env[i], '='))
		{
			ft_putstr_fd(m_env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	return (0);
}
