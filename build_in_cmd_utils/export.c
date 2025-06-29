/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:32 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:16:32 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	update_variable(char *s, char **env, int i)
{
	if (env[i] != NULL)
		free(env[i]);
	env[i] = ft_strdup(s);
	if (!env[i])
		return (1);
	return (0);
}

char	**add_variable(char **env, const char *new_var, int current_size)
{
	char	**new_env;

	new_env = ft_realloc(env, ((current_size + 1) * sizeof(char *)),
			(current_size + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_putstr_fd("Memory allocation failed----------------\n", 2);
		return (env);
	}
	new_env[current_size] = ft_strdup(new_var);
	if (!new_env[current_size])
	{
		ft_putstr_fd("Memory allocation failed**************\n", 2);
		return (env);
	}
	new_env[current_size + 1] = NULL;
	return (new_env);
}

int	exports(char *var, char ***env)
{
	int		i;
	int		found;
	char	**temp;
	char	**split;

	split = ft_split(var, '=');
	if (!split)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	i = 0;
	found = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], split[0], strlen(split[0])) == 0)
		{
			if (ft_strchr(var, '='))
			{
				if (update_variable(var, *env, i))
				{
					free_split(split);
					return (1);
				}
				found = 1;
				break ;
			}
			else
			{
        ft_free_tab(split);
				return (0);
			}
		}
		i++;
	}
	if (!found)
	{
		temp = add_variable(*env, var, i);
		if (!temp)
		{
			free_split(split);
			return (1);
		}
		*env = temp;
	}
	free_split(split);
	return (0);
}
