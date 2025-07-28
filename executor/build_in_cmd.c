/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:12 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 05:15:25 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
  save_fds(minishell->red);
  redirection(minishell->red);
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
		minishell->status = ft_my_exit(minishell);
  restore_fds(minishell->red);
}
