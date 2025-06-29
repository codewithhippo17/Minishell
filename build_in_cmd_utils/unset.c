/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:13:59 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:59 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (j < l)
	{
		split = ft_split(env[j], '=');
		if (!split)
			return (NULL);
		if (env[j] && ft_strncmp(split[0], var, ft_strlen(split[0])) != 0)
		{
			new_env[i] = ft_strdup(env[j]);
			if (!new_env[i])
			{
				ft_free_tab(split);
				ft_free_tab(new_env);
				return (NULL);
			}
			i++;
		}
		j++;
	}
	while (i < l)
		new_env[i++] = NULL;
	ft_free_tab(split);
	ft_free_tab(env);
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
			ft_free_tab(split);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_env(char *var, char ***env)
{
	char	**temp;

	if (!if_ixist(var, *env))
		return (0);
	temp = rm_var(var, *env);
	if (!temp)
		return (1);
	*env = temp;
	return (0);
}
