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
#include <stdlib.h>

int	find_variable(char *var, char **env, int *pos)
{
	int		i;
	int		found;
	char	**splited_var;
	char	**splited_env;

	i = 0;
	found = 0;
	splited_var = ft_split(var, '=', SCOPE_TEMP);
	while (env[i])
	{
		splited_env = ft_split(env[i], '=', SCOPE_TEMP);
		if (ft_strcmp(splited_env[0], splited_var[0]) == 0)
		{
			found = 1;
			break ;
		}
		splited_env = NULL;
		i++;
	}
	*pos = i;
	return (found);
}

// char	**add_variable(char **env, const char *new_var, int current_size)
// {
// 	char	**new_env;
//
// 	new_env = ft_realloc(env, ((current_size + 1) * sizeof(char *)),
// 			(current_size + 2) * sizeof(char *));
//     collector_register(new_env, SCOPE_SHELL);
// 	new_env[current_size] = ft_strdup(new_var, SCOPE_SHELL);
// 	new_env[current_size + 1] = NULL;
// 	return (new_env);
// }

char **add_variable(char **env, const char *new_var, int current_size)
{
	int i;
	char **new_env;

	i = 0;
	new_env = my_alloc((current_size + 2) * sizeof(char *), SCOPE_SHELL);
	while (env[i]) 
	{
		new_env[i] = ft_strdup(env[i], SCOPE_SHELL);
		i++;
	}
	new_env[i] = ft_strdup(new_var, SCOPE_SHELL);
	new_env[i + 1] = NULL;
	return (new_env);
}


int	update_variable(char *var, char **env, int found)
{
	if (ft_strchr(var, '='))
	{
		env[found] = ft_strdup(var, SCOPE_SHELL);
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
		update_variable(var, *env, pos);
	}
    collector_cleanup(SCOPE_TEMP);
	return (0);
}
