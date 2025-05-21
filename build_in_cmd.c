#include "minishell.h"

int	is_builtin(char **s)
{
	if (ft_strncmp(s[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "env", ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "export", ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(s[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "echo", ft_strlen("echo")) == 0)
	{
		minishell->status = echo(minishell->input, minishell->status);
	}
	else if (ft_strncmp(minishell->cmd_args[0], "cd", ft_strlen("cd")) == 0)
		minishell->status = cd(minishell->cmd_args[1], minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd", ft_strlen("pwd")) == 0)
		minishell->status = pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "env", ft_strlen("env")) == 0)
		minishell->status = envierment(minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen("export")) == 0)
		minishell->status = ft_export(minishell->cmd_args[1],
				minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "exit", ft_strlen("exit")) == 0)
	{
		if (minishell->cmd_args[1])
			exit(ft_atoi(minishell->cmd_args[1]));
		else
			exit(0);
	}
}
