/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:49:32 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/02 16:49:32 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (1);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	handle_export_arg(t_minishell *minishell, t_script *script, int i)
{
	int	status;
	int	valid_var;

	status = 0;
	valid_var = is_var(script->cmd_args[i]);
	if (valid_var == 0)
	{
		status = exports(script->cmd_args[i], &(minishell->s_env));
		if (status == 0)
			status = exports(script->cmd_args[i], &(minishell->m_env));
	}
	else
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(script->cmd_args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (status);
}

int	print_sorted_env(char **env, int i, int j)
{
	char	**split;

	while (env[++i])
	{
		j = 0;
		split = ft_split(env[i], '=', SCOPE_TEMP);
		if (ft_strchr(env[i], '=') && ft_strcmp(split[0], "_"))
		{
			printf("declare -x %s=\"", split[0]);
			while (split[++j])
			{
				printf("%s", split[j]);
				if (split[j + 1])
					printf("=");
			}
			printf("\"\n");
		}
		else if (ft_strcmp(split[0], "_"))
			printf("declare -x %s\n", env[i]);
	}
	return (0);
}

int	declair_x(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = i;
		while (env[++j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				ft_swap_str(&env[i], &env[j]);
		}
	}
	if (print_sorted_env(env, -1, 0))
		return (1);
	return (0);
}

int	exec_export(t_minishell *minishell, t_script *script)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (script->cmd_args[i])
	{
		while (script->cmd_args[i])
		{
			if (handle_export_arg(minishell, script, i++))
				status = 1;
		}
	}
	else
		status = declair_x(minishell->m_env);
	return (status);
}
