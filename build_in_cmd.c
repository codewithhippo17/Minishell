/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:14:12 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	is_var(char *str)
{
	int	i;

	if (!str || !*str)
		return (2);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (2);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (2);
		i++;
	}
	if (str[i] == '=')
		return (0);
	return (1);
}

int	handle_export_arg(t_minishell *minishell, int i)
{
	int	status;
	int	valid_var;

	status = 0;
	valid_var = is_var(minishell->cmd_args[i]);
	if (valid_var == 0)
	{
		status = exports(minishell->cmd_args[i], &(minishell->s_env));
		if (status == 0)
			status = exports(minishell->cmd_args[i], &(minishell->m_env));
	}
	else if (valid_var == 1)
		status = exports(minishell->cmd_args[i], &(minishell->s_env));
	else
		status = 1;
	if (status != 0)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(minishell->cmd_args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (status);
}

int	exec_export(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (minishell->cmd_args[i])
	{
		while (minishell->cmd_args[i])
		{
			status = handle_export_arg(minishell, i);
			i++;
		}
	}
	else
	{
		status = envierment(minishell->s_env);
	}
	return (status);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_my_exit(char *e_xit)
{
	if (e_xit && is_num(e_xit))
		exit(ft_atoi(e_xit));
	else
		exit(EXIT_SUCCESS);
}

int	exec_unset(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (minishell->cmd_args[i])
	{
		status = unset_env(minishell->cmd_args[i], &(minishell->m_env));
		if (!status)
			status = unset_env(minishell->cmd_args[i], &(minishell->s_env));
		else
			return (1);
		i++;
	}
	return (status);
}

void	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "echo",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = echo(minishell->input, minishell->status);
	else if (ft_strncmp(minishell->cmd_args[0], "cd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = cd(minishell->cmd_args[1], minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd",
			ft_strlen(minishell->cmd_args[0])) == 0 && !minishell->cmd_args[1])
		minishell->status = pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "env",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = envierment(minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = exec_export(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "unset",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = exec_unset(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "exit",
			ft_strlen(minishell->cmd_args[0])) == 0)
	{
		ft_my_exit(minishell->cmd_args[1]);
		/*
			if (minishell->cmd_args[1])
				exit(ft_atoi(minishell->cmd_args[1]));
			else
				exit(EXIT_SUCCESS);*/
	}
}
