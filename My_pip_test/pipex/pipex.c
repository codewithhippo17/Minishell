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

static void	child_pr(char *infile, char *cmd1, int *p_fd, int flag, char **env)
{
	int		in_fd;
	char	**args;
	char	*path_1;

  if (flag)
  {
    in_fd = open(infile, O_RDONLY);
	  if (in_fd == -1)
		  ft_exit("open", EXIT_FAILURE);
	  dup2(in_fd, STDIN_FILENO);
  }
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
		child_pr(av[0], av[1], p_fd, l_flag, env);
	else
	{
		pid2 = fork();
		if (pid2 == -1)
			ft_exit("fork", EXIT_FAILURE);
		else if (pid2 == 0)
			parent_pr(av[2], av[3], p_fd, r_flag, env);
		else
			ft_close_wait_exit(p_fd, pid1, pid2);
	}
}




#include "pipex.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void	parcing_pipex(char *input, char **env)
{
	char	**args;
	char	**left;
	char	**right;
	char	*cmd1;
	char	*cmd2;
	char	*infile = NULL;
	char	*outfile = NULL;
	int		flag = 0;
  int   l_flag = 0;

	if (!ft_strchr(input, '|'))
		ft_exit("missing pipe |", 1);

	args = ft_split(input, '|');
	if (!args[0] || !args[1])
		ft_exit("invalid pipe syntax", 1);

	left = ft_split(args[0], ' ');
	right = ft_split(args[1], ' ');

	// parse infile + cmd1
	int i = 0;
	if ((ft_strncmp(left[0], "<", ft_strlen(left[0])) == 0) && (access(left[1], F_OK) == 0))
	{
    printf("%s\n", "************************************");
		infile = ft_strdup(left[1]);
		i = 2;
    l_flag = 1;
	}
	else if ((ft_strncmp(left[1], "<", strlen(left[1]) == 0)) && access(left[2], F_OK) == 0)
	{
    printf("%s\n", "------------------------------------");
		infile = ft_strdup(left[2]);
		i = 0;
    l_flag = 1;
	}
	if ((ft_strncmp(left[1], "<", ft_strlen(left[1])) != 0) && (access(left[1], F_OK) == 0))
	{
    printf("%s\n", "+++++++++++++++++++++++++++++++++++++");
    infile = ft_strdup(left[1]);
    i = 0;
    l_flag = 1;
  }

  printf("%s\n", infile);
	cmd1 = ft_strdup(left[i]);
  printf("%s\n", cmd1);
	while (left[++i])
	{
		char *tmp = ft_strjoin(cmd1, " ");
		free(cmd1);
		cmd1 = ft_strjoin(tmp, left[i]);
		free(tmp);
	}

	// parse outfile + cmd2
	i = 0;
	while (right[i])
	{ 
    while (right[i])
	  {
		  if (right[i][0] == '>' && right[i][1] == '>' && right[i][2] == '\0')
		  {
			  outfile = ft_strdup(right[i + 1]);
			  flag = 2;
			  right[i] = NULL;
			  break;
		  }
		  else if (right[i][0] == '>' && right[i][1] == '\0')
		  {
			  outfile = ft_strdup(right[i + 1]);
			  flag = 1;
			  right[i] = NULL;
			  break;
		  }
		  i++;
	  }
	}

	cmd2 = ft_strdup(right[0]);
	for (i = 1; right[i]; i++)
	{
		char *tmp = ft_strjoin(cmd2, " ");
		free(cmd2);
		cmd2 = ft_strjoin(tmp, right[i]);
		free(tmp);
	}

	// create argv for pipex
	char *argv[5] = {infile, cmd1, cmd2, outfile, NULL};
	pipex(argv, env, l_flag, flag);

	ft_free_tab(args);
	ft_free_tab(left);
	ft_free_tab(right);
	free(cmd1);
	free(cmd2);
	if (infile) free(infile);
	if (outfile) free(outfile);
}

/*
void rederection_handler(chat *input);
{
  int i = 0;
  while (input[i])
  {
    if ()
  }
}*/

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

/*
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

*/
