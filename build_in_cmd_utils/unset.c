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
#include <string.h>

int	set_flag(char *var)
{
	if (ft_strncmp(var, "PWD", ft_strlen("PWD")) == 0)
		return (1);
	else if (ft_strncmp(var, "OLDPWD", ft_strlen("OLDPWD")) == 0)
		return (1);
	return (0);
}

char	**rm_var(char *var, char **env)
{
	int		i;
	int		j;
	int		l;
	char	**new_env;

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
		if (ft_strncmp(env[j], var, ft_strlen(var)) != 0)
		{
			new_env[i] = ft_strdup(env[j]);
			if (!new_env[i])
			{
				ft_free_tab(new_env);
				return (NULL);
			}
			i++;
		}
		j++;
	}
	while (i < l)
		new_env[i++] = NULL;
	ft_free_tab(env);
	return (new_env);
}

int	if_ixist(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	unset_env(char *var, char ***env)
{
	int		i;
	int		l;
	int		flag;
	char	**temp;

	i = 0;
	l = 0;
	if (!if_ixist(var, *env))
		return (0);
	while ((*env)[l])
		l++;
	flag = set_flag(var);
	if (!flag)
	{
		temp = rm_var(var, *env);
		if (!temp)
			return (1);
		*env = temp;
	}
	else
	{
		while (i < l)
		{
			if (ft_strncmp((*env)[i], var, ft_strlen(var)) == 0)
			{
				if ((*env)[i] != NULL)
					free((*env)[i]);
				(*env)[i] = ft_strdup(var);
				if (!(*env)[i])
					return (1);
			}
			i++;
		}
	}
	return (0);
}
