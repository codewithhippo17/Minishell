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

static void	child_pr(char *infile, char *cmd1, int *p_fd, char **env)
{
	int		in_fd;
	char	**args;
	char	*path_1;

	in_fd = open(infile, O_RDONLY);
	if (in_fd == -1)
		ft_exit("open", EXIT_FAILURE);
	close(p_fd[0]);
	dup2(p_fd[1], STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
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

static void	parent_pr(char *cmd2, char *outfile, int *p_fd, int flag,
		char **env)
{
	int		out_fd;
	char	**args;
	char	*path_2;

	if (flag && outfile)
	{
		if (flag == 1)
		{
			out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (out_fd == -1)
				ft_exit("open", EXIT_FAILURE);
		}
		else
		{
			out_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out_fd == -1)
				ft_exit("open", EXIT_FAILURE);
		}
		dup2(out_fd, STDOUT_FILENO);
	}
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

void	pipex(char **av, char **env, int flag)
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
		child_pr(av[0], av[1], p_fd, env);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit("fork", EXIT_FAILURE);
		else if (pid2 == 0)
			parent_pr(av[2], av[3], p_fd, flag, env);
		else
			ft_close_wait_exit(p_fd, pid1, pid2);
	}
}

void	parcing_pipex(char *input, char **env)
{
	int		l;
	int		i;
	int		j;
	int		flag;
	char	**arr;
	char	*ar;
	char	**av;
	char	*at;
	char	*tmp;
	char	*iiin;

	l = 0;
	i = 0;
	j = 0;
	flag = 0;
	while (input[l])
		l++;
	if ((ft_strchr(input, '<') && ft_strchr(input, '>')) && ft_strchr(input,
			'|'))
	{
		ar = malloc(l * sizeof(char));
		while (i < l)
		{
			if (input[i] == '<' || input[i] == '|')
			{
				i++;
			}
			else if (input[i] == '>' && input[i + 1] != '>')
			{
				i++;
				flag = 1;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				i += 2;
				flag = 2;
			}
			else
			{
				ar[j++] = input[i];
			}
			i++;
		}
		printf("%s\n", ar);
		av = ft_split(ar, ' ');
		pipex(av, env, flag);
	}
	else
	{
		i = 1;
		av = ft_split(input, ' ');
		tmp = av[0];
		av[0] = av[1];
		av[1] = tmp;
		printf("%s\n", av[0]);
		at = ft_strjoin(av[0], "");
		while (av[i])
		{
			at = ft_strjoin(at, " ");
			at = ft_strjoin(at, av[i++]);
		}
		printf("%s\n", at);
		i = 0;
		j = 0;
		iiin = malloc(l * sizeof(char));
		while (i < l)
		{
			if (at[i] == '|')
				i++;
			else if (at[i] == '>' && at[i + 1] != '>')
			{
				i++;
				flag = 1;
			}
			else if (at[i] == '>' && at[i + 1] == '>')
			{
				i += 2;
				flag = 2;
			}
			else
				iiin[j++] = at[i];
			i++;
		}
		printf("%s\n", iiin);
		arr = ft_split(iiin, ' ');
		printf("%s\n", arr[3]);
		pipex(arr, env, flag);
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
