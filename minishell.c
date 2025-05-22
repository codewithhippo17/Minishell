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

void	handle_command(t_minishell *minishell)
{
	if (is_builtin(minishell->cmd_args))
		execute_builtin(minishell);
	else
	{
		minishell->status = ft_exec_all(minishell);
	}
	free(minishell->input);
}

void set_env(t_minishell *minishell, char **env)
{
  int			l;
	int			i;

	l = 0;
	i = 0;
  while (env && env[l])
		l++;
	minishell->m_env = malloc((l + 1) * sizeof(char *));
	while (env && env[i])
	{
		minishell->m_env[i] = ft_strdup(env[i]);
		if (!minishell->m_env[i])
		{
			printf("Memory allocation failed\n");
			free_split(minishell->m_env);
			return ;
		}
		i++;
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
  
  set_env(minishell, env);
	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$");
		add_history(minishell->input);
    if (minishell->input == NULL)
      exit(EXIT_SUCCESS);
		minishell->cmd_args = ft_split(minishell->input, ' ');
		if (!minishell->cmd_args)
		{
			free(minishell->input);
			free(minishell);
			return (EXIT_FAILURE);
		}
		handle_command(minishell);
    printf("%d\n", minishell->status);
		free_split(minishell->cmd_args);
	}
	free(minishell);
	return (EXIT_SUCCESS);
}
