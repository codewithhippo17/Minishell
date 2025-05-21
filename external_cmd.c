#include "minishell.h"

static void	child_pr(char **cmd, char **env)
{
	char	*path;

	path = get_path(cmd[0], env);
	execve(path, cmd, env);
	free_split(cmd);
	exit(127);
}

int	ft_exec_all(t_minishell *minishell)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		ft_exit("fork: Error\n");
	else if (pid == 0)
		child_pr(minishell->cmd_args, minishell->m_env);
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
