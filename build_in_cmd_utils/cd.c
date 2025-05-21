#include "../minishell.h"

int	cd(char *str, char **m_env)
{
	char		*home;
	char		*prev_dir;
	char	  current_dir[1024];

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (str == NULL || *str == '\0' || ft_strncmp(str, "~",
			ft_strlen("~")) == 0)
	{
		home = getenv("HOME");
		if (home == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		str = home;
	}
	else if (ft_strncmp(str, "-", ft_strlen("-")) == 0)
	{
		prev_dir = my_getenv("OLDPWD", m_env);
		if (prev_dir != NULL)
		{
			str = prev_dir;
			printf("%s\n", prev_dir);
		}
		else
		{
			fprintf(stderr, "No previous directory\n");
			return (1);
		}
	}
	if (chdir(str) != 0)
	{
		perror("cd error");
		return (1);
	}
	prev_dir = ft_strjoin("OLDPWD=", current_dir);
	ft_export(prev_dir, m_env);
	return (0);
}
