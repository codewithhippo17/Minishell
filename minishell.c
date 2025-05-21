#include "minishell.h"

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

int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
	int			l;
	int			i;

	l = 0;
	i = 0;
	minishell = malloc(sizeof(t_minishell));

  //More thinking i my revamp it to be env.c well see
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
			return (1);
		}
		i++;
	}

	while (argc == 1 && argv)
	{
		minishell->input = readline("minishell$");
		add_history(minishell->input);
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
