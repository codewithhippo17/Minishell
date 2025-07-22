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
#include <stdlib.h>

char	**rm_var(char *var, char **env)
{
	int		i;
	int		j;
	int		l;
	char	**new_env;
	char	**split;

	i = 0;
	j = 0;
	l = 0;
	while (env[l])
		l++;
	new_env = malloc((l) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[j])
	{
		split = ft_split(env[j], '=');
		if (!split)
			return (NULL);
		if (ft_strcmp(split[0], var) != 0)
		{
			new_env[i] = ft_strdup(env[j]);
			if (!new_env[i])
			{
				free_strings(split);
				free_strings(new_env);
				return (env);
			}
			i++;
		}
		free_strings(split);
		j++;
	}
	new_env[i] = NULL;
	free_strings(env);
	return (new_env);
}

int	if_ixist(char *var, char **env)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return (0);
		if (ft_strncmp(split[0], var, ft_strlen(split[0])) == 0)
		{
			free_strings(split);
			return (1);
		}
		free_strings(split);
		i++;
	}
	return (0);
}

int	unset_env(char *var, char ***env)
{
	char	**tmp;

	if (!if_ixist(var, *env))
		return (0);
	tmp = rm_var(var, *env);
	if (!(tmp))
		return (1);
	*env = tmp;
	return (0);
}
