#include "minishell.h"

void	free_split(char **s)
{
	int	j;

	j = 0;
	while (s[j])
	{
		free(s[j]);
		j++;
	}
	free(s);
}

void	ft_exit(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}
