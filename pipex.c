/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:44 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:15:44 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pr(char *infile, char *cmd1, int *p_fd, char **env)
{
	int		in_fd;
	char	**args;
	char	*path_1;

	in_fd = open(infile, O_RDONLY);
	if (in_fd == -1)
		ft_exit_status("open", EXIT_FAILURE);
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
	args = ft_split(cmd1, ' ');
	if (!args)
		ft_exit_status("ft_split", EXIT_FAILURE);
	if (args[0] == NULL)
		ft_free_exit(args, "ft_split", EXIT_FAILURE);
	path_1 = get_path(args[0], env);
	execve(path_1, args, env);
	ft_free_exit(args, "execve", 127);
}

static void	child_pr2(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "cd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		cd(minishell->cmd_args[1], minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "echo",
			ft_strlen(minishell->cmd_args[0])) == 0)
		echo(minishell->input, minishell->status);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen(minishell->cmd_args[0])) == 0)
		exec_export(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "env",
			ft_strlen(minishell->cmd_args[0])) == 0)
		envierment(minishell->s_env);
	else if (ft_strncmp(minishell->cmd_args[0], "exit",
			ft_strlen(minishell->cmd_args[0])) == 0)
		exit(0);
}

static void	parent_pr(char *cmd2, char *outfile, int *p_fd, char **env)
{
	int		out_fd;
	char	**args;
	char	*path_2;

	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd == -1)
		ft_exit_status("open", EXIT_FAILURE);
	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	args = ft_split(cmd2, ' ');
	if (!args)
		ft_exit_status("ft_split", EXIT_FAILURE);
	if (args[0] == NULL)
		ft_free_exit(args, "ft_split", EXIT_FAILURE);
	path_2 = get_path(args[0], env);
	execve(path_2, args, env);
	ft_free_exit(args, "execve", 127);
}

static void	parent_pr2(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "cd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		cd(minishell->cmd_args[1], minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "echo",
			ft_strlen(minishell->cmd_args[0])) == 0)
		echo(minishell->input, minishell->status);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen(minishell->cmd_args[0])) == 0)
		exec_export(minishell);
	else if (ft_strncmp(minishell->cmd_args[0], "env",
			ft_strlen(minishell->cmd_args[0])) == 0)
		envierment(minishell->s_env);
	else if (ft_strncmp(minishell->cmd_args[0], "exit",
			ft_strlen(minishell->cmd_args[0])) == 0)
		exit(0);
}
void	pipex(t_minishell *minishell)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(p_fd) == -1)
		ft_exit_status("pipe", EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		ft_exit_status("fork", EXIT_FAILURE);
	else if (pid1 == 0)
	{
		if (is_builtin(minishell->cmd_args) == 1)
			child_pr2(minishell);
		else
			child_pr(minishell->cmd_args[1], minishell->cmd_args[2], p_fd,
				minishell->m_env);
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit_status("fork", EXIT_FAILURE);
		else if (pid2 == 0)
		{
			if (is_builtin(minishell->cmd_args) == 1)
				parent_pr2(minishell);
			else
				parent_pr(minishell->cmd_args[3], minishell->cmd_args[4], p_fd,
					minishell->m_env);
		}
		else
			ft_close_wait_exit(p_fd, pid1, pid2);
	}
}
