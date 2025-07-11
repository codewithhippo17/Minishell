#include "minishell.h"

char	**set_env_utils(char **env)
{
	int		i;
	int		l;
	char	**my_env;

	i = 0;
	l = 0;
	while (env[l])
		l++;
	my_env = malloc((l + 1) * sizeof(char *));
	if (!my_env)
	{
		ft_putstr_fd("Memory allocation failed\n", 2);
		free_strings(my_env);
		return (NULL);
	}
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		if (!my_env[i])
		{
			ft_putstr_fd("Memory allocation failed\n", 2);
			free_strings(my_env);
			return (NULL);
		}
		i++;
	}
	my_env[i] = NULL;
	return (my_env);
}

int	set_env(t_minishell *minishell, char **env)
{
	minishell->m_env = set_env_utils(env);
	if (!minishell->m_env)
		return (1);
	minishell->s_env = set_env_utils(env);
	if (!minishell->s_env)
		return (1);
	unset_env("_", &(minishell->s_env));
	if (!minishell->s_env)
		return (1);
	return (0);
}
