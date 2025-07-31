/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/31 04:35:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_unset(t_minishell *minishell)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (minishell->script->cmd_args[i])
	{
		status = unset_env(minishell->script->cmd_args[i], &(minishell->m_env));
		if (status)
			return (1);
		i++;
	}
	return (status);
}

int	execute_builtin(t_minishell *minishell, t_script *script)
{
	int	flag;

  flag = 0;
	if (script->red)
	{
		save_fds(script->red);
		flag = redirection(script->red);
		minishell->status = flag;
	}
	if (flag == 0)
	{
		if (ft_strcmp(script->cmd_args[0], "echo") == 0)
			minishell->status = echo(script->cmd_args);
		else if (ft_strcmp(script->cmd_args[0], "cd") == 0)
			minishell->status = cd(script->cmd_args, minishell);
		else if (ft_strcmp(script->cmd_args[0], "pwd") == 0)
			minishell->status = pwd();
		else if (ft_strcmp(script->cmd_args[0], "env") == 0)
			minishell->status = envierment(minishell->m_env);
		else if (ft_strcmp(script->cmd_args[0], "export") == 0)
			minishell->status = exec_export(minishell);
		else if (ft_strcmp(script->cmd_args[0], "unset") == 0)
			minishell->status = exec_unset(minishell);
		else if (ft_strcmp(script->cmd_args[0], "exit") == 0)
			minishell->status = ft_my_exit(minishell);
	}
	if (script->red)
		restore_fds(script->red);
	return (minishell->status);
}
