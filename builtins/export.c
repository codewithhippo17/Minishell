/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:16:32 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:45:30 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

int	find_variable(char *var, char **env, int *pos)
{
	int		i;
	int		found;
	char	**splited_var;
	char	**splited_env;

	i = 0;
	found = 0;
	splited_var = ft_split(var, '=');
	if (!splited_var)
		return (printf("Memory allocation failed\n"), 1);
	while (env[i])
	{
		splited_env = ft_split(env[i], '=');
		if (ft_strcmp(splited_env[0], splited_var[0]) == 0)
		{
			free_strings(splited_env);
			found = 1;
			break ;
		}
		free_strings(splited_env);
		splited_env = NULL;
		i++;
	}
	*pos = i;
	return (found);
}

char	**add_variable(char **env, const char *new_var, int current_size)
{
	char	**new_env;

	new_env = ft_realloc(env, ((current_size + 1) * sizeof(char *)),
			(current_size + 2) * sizeof(char *));
	if (!new_env)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		return (env);
	}
	new_env[current_size] = ft_strdup(new_var);
	if (!new_env[current_size])
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		return (env);
	}
	new_env[current_size + 1] = NULL;
	return (new_env);
}

int	update_variable(char *var, char **env, int found)
{
	if (ft_strchr(var, '='))
	{
		if (env[found] != NULL)
			free(env[found]);
		env[found] = ft_strdup(var);
		if (!env[found])
			return (1);
	}
	return (0);
}

int	exports(char *var, char ***env)
{
	int		pos;
	int		found;
	char	**temp_env;

	found = find_variable(var, *env, &pos);
	if (!found)
	{
		temp_env = add_variable(*env, var, pos);
		if (!temp_env)
			return (1);
		*env = temp_env;
	}
	else
	{
		if (update_variable(var, *env, pos))
			return (1);
	}
	return (0);
}
