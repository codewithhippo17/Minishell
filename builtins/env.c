/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:10:42 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/11 23:53:15 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	envierment(char **m_env)
{
	int		i;
	char	*env;

	env = NULL;
	i = 0;
	while (m_env[i])
	{
		if (ft_strncmp(m_env[i], "_=", 2) == 0)
		{
			env = m_env[i++];
			continue ;
		}
		if (ft_strchr(m_env[i], '='))
		{
			ft_putstr_fd(m_env[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	if (env)
		printf("%s\n", env);
	return (0);
}
