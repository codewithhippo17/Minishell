/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:19 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/06 19:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	printerror(char *cmd, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(err, 2);
}

static void	child_pr_all(t_minishell *mini)
{
	char	*path;

	if (ft_strchr(mini->cmd_args[0], '/'))
	{
		if (access(mini->cmd_args[0], F_OK) == -1)
		{
			printerror(mini->cmd_args[0], ": No such file or directory\n");
			free_strings(mini->cmd_args);
			free_exit_minishell(mini, 127);
		}
		else if (access(mini->cmd_args[0], X_OK) == -1)
		{
			printerror(mini->cmd_args[0], ": Permission denied\n");
			free_strings(mini->cmd_args);
			free_exit_minishell(mini, 126);
		}
		else if (opendir(mini->cmd_args[0]))
		{
			printerror(mini->cmd_args[0], ": Is a directory\n");
			free_strings(mini->cmd_args);
			free_exit_minishell(mini, 126);
		}
		path = ft_strdup(mini->cmd_args[0]);
	}
	else
	{
		path = get_path(mini->cmd_args[0], mini->m_env);
		if (!path)
		{
			printerror(mini->cmd_args[0], ": command not found\n");
			free_strings(mini->cmd_args);
			free_exit_minishell(mini, 127);
		}
	}
	execve(path, mini->cmd_args, mini->m_env);
	free(path);
	free_strings(mini->cmd_args);
	free_exit_minishell(mini, 127);
}

int	ft_exec_all(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free_exit_minishell(minishell, 1);
	}
	if (pid == 0)
		child_pr_all(minishell);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (status);
}
