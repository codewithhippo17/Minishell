/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:49:14 by marvin            #+#    #+#             */
/*   Updated: 2025/05/11 00:33:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

void	update_variable(char **s, char **env, int index)
{
	char	*temp;

	free(env[index]);
	env[index] = ft_strjoin(s[0], "=");
	temp = ft_strjoin(env[index], s[1]);
	free(env[index]);
	env[index] = temp;
}

void	add_variable(char *s, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	env[i] = ft_strdup(s);
  if (!env[i])
    return ;
	env[i + 1] = NULL;
}

int	exports(char *var, char **env)
{
	char	**s;
	int		i;
	int		found;

	s = ft_split(var, '=');
	if (!s)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	i = 0;
	found = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s[0], strlen(s[0])) == 0)
		{
			update_variable(s, env, i);
			found = 1;
			break ;
		}
		i++;
	}
	if (!found)
		add_variable(var, env);
	free_split(s);
  return (0);
}

int	ft_export(char **av, char **env)
{
  int i;

  i = 0;
  if (av[++i])
  {
    while (av[i])
    {
		  if (exports(av[i++], env) != 0)
        return (1);
    }
  }
	else
  {
    i = 0;
	  while (env[i])
	  {
		  printf("%s\n", env[i++]);
	  }
  }
  return (0);
}
