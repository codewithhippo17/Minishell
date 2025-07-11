/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:53:32 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:53:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

static void	child_pr(char *cmd1, int *p_fd, char **env)
{
	char	**args;
	char	*path_1;

	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	args = ft_split(cmd1, ' ');
	if (!args)
		ft_exit("ft_split", EXIT_FAILURE);
	if (args[0] == NULL)
		ft_free_exit(args, "ft_split", EXIT_FAILURE);
	path_1 = get_path(args[0], env);
	if ((ft_strncmp(args[0], "sudo", ft_strlen(args[0])) == 0)
		&& (execve(path_1, args, env) == -1))
	{
		ft_free_exit(args, "sudo", 126);
	}
	if (execve(path_1, args, env) == -1)
		ft_free_exit(args, "execve", 127);
}

static void	parent_pr(char *cmd2, int *p_fd, char **env)
{
	char	**args;
	char	*path_2;

	close(p_fd[1]);
	dup2(p_fd[0], STDIN_FILENO);
	args = ft_split(cmd2, ' ');
	if (!args)
		ft_exit("ft_split", EXIT_FAILURE);
	if (args[0] == NULL)
		ft_free_exit(args, "ft_split", EXIT_FAILURE);
	path_2 = get_path(args[0], env);
	if ((ft_strncmp(args[0], "sudo", ft_strlen(args[0])) == 0)
		&& (execve(path_2, args, env) == -1))
	{
		ft_free_exit(args, "sudo", 126);
	}
	if (execve(path_2, args, env) == -1)
		ft_free_exit(args, "execve", 127);
}



void	pipex(char **av, char **env, int l_flag, int r_flag)
{
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(p_fd) == -1)
		ft_exit("pipe", EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == -1)
		ft_exit("fork", EXIT_FAILURE);
	else if (pid1 == 0)
		child_pr(av[0], p_fd, env);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit("fork", EXIT_FAILURE);
		else if (pid2 == 0)
			parent_pr(av[2], p_fd, env);
		else
			ft_close_wait_exit(p_fd, pid1, pid2);
	}
}


void rederection_handler(char *input);
{
  char srgs = ft_split(input, '|');
  int i = 0;
  while (input[i])
  {
    if ()
  }
}



int	main(int ac, char **av, char **env)
{
	int		i;
	char	*temp;
	char	*input;

	i = 1;
	if (ac < 3)
	{
		ft_putstr_fd("Usage: %s cmd1 | cmd2\n", 2);
		ft_putstr_fd("Usage: %s cmd1 infile | cmd2\n", 2);
		ft_putstr_fd("Usage: %s cmd1 infile | cmd2 > outfile\n", 2);
		ft_putstr_fd("Usage: %s < infile cmd1 | cmd2 > outfile\n", 2);
		ft_putstr_fd("Usage: %s < infile cmd1 | cmd2\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (ac >= 4)
	{
		input = ft_strjoin(av[i], "");
		while (av[i] && av[i + 1])
		{
			temp = ft_strjoin(input, " ");
			input = ft_strjoin(temp, av[i + 1]);
			i++;
		}
		printf("%s\n", input);
		parcing_pipex(input, env);
	}
	return (0);
}
