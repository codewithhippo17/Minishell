#include "minishell.h"

void	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_args[0], "echo",
			ft_strlen(minishell->cmd_args[0])) == 0)
	{
		minishell->status = echo(minishell->input, minishell->status);
	}
	else if (ft_strncmp(minishell->cmd_args[0], "cd",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = cd(minishell->cmd_args[1], minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "pwd",
			ft_strlen(minishell->cmd_args[0])) == 0 && !minishell->cmd_args[1])
		minishell->status = pwd();
	else if (ft_strncmp(minishell->cmd_args[0], "env",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = envierment(minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "export",
			ft_strlen(minishell->cmd_args[0])) == 0)
		minishell->status = ft_export(minishell->cmd_args, minishell->m_env);
	else if (ft_strncmp(minishell->cmd_args[0], "exit",
			ft_strlen(minishell->cmd_args[0])) == 0)
	{
		if (minishell->cmd_args[1])
			exit(ft_atoi(minishell->cmd_args[1]));
		else
			exit(EXIT_SUCCESS);
	}
}
