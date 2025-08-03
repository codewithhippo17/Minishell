/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 03:22:19 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 03:23:57 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**set_env_utils(char **env)
{
	int		i;
	int		l;
	char	**my_env;

	i = 0;
	l = 0;
	while (env[l])
		l++;
	my_env = (char **)my_alloc((l + 1) * sizeof(char *), SCOPE_SHELL);
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i], SCOPE_SHELL);
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

void	set_env(t_minishell *minishell, char **env)
{
	minishell->m_env = set_env_utils(env);
	minishell->s_env = set_env_utils(env);
}
