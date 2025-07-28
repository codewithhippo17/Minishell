/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:14:19 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 01:48:49 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

static void	printerror(t_minishell *mini, char *err, int exinum)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(mini->cmd_args[0], 2);
	ft_putstr_fd(err, 2);
	free_strings(mini->cmd_args);
	free_exit_minishell(mini, exinum);
	exit (exinum);
}

static void	child_pr_all(t_minishell *mini)
{
	char		*path;
	struct stat	stats;

	if (ft_strchr(mini->cmd_args[0], '/'))
	{
		stat(mini->cmd_args[0], &stats);
		if (access(mini->cmd_args[0], F_OK) == -1)
			printerror(mini, ": No such file or directory\n", 127);
		else if (S_ISDIR(stats.st_mode))
			printerror(mini, ": Is a directory\n", 126);
		path = ft_strdup(mini->cmd_args[0]);
	}
	else
	{
		path = get_path(mini->cmd_args[0], mini->m_env);
		if (!path)
			printerror(mini, ": command not found\n", 127);
	}
    if (mini->red)
    {
        if (redirection(mini->red) == -1)
            printerror(mini, "Error: Redirection failed", 1);
    }
    execve(path, mini->cmd_args, mini->m_env);
	free(path);
	printerror(mini, ": Permission denied\n", 126);
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
