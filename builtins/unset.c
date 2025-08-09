/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:13:59 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/22 03:10:12 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rm_var(char *var, char **env)
{
	int		i;
	int		j;
	int		l;
	char	**new_env;
	char	**temp;

	i = 0;
	j = 0;
	l = 0;
	while (env[l])
		l++;
	new_env = my_alloc((l) * sizeof(char *), SCOPE_SHELL);
	while (env[j])
	{
		temp = ft_split(env[j], '=', SCOPE_TEMP);
		if (ft_strcmp(temp[0], var) != 0)
		{
			new_env[i] = ft_strdup(env[j], SCOPE_SHELL);
			i++;
		}
		j++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	if_ixist(char *var, char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=', SCOPE_TEMP);
		if (ft_strcmp(split[0], var) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	unset_env(char *var, char ***env)
{
	char	**tmp;

	if (!var)
		return (0);
	if (!if_ixist(var, *env))
		return (0);
	tmp = rm_var(var, *env);
	if (!(tmp))
		return (1);
	*env = tmp;
	return (0);
}
