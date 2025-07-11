/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:53:32 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:53:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	if (!name || !env)
		return (NULL);
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!sub)
			return (NULL);
		if (ft_strncmp(sub, name, ft_strlen(sub)) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int	i;

	char *(exec), *(path_part);
	char **(allpath), **(s_cmd);
	i = -1;
	if (!cmd || !env)
		return (NULL);
	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		ft_exit("ft_split", EXIT_FAILURE);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
		ft_exit("ft_split", EXIT_FAILURE);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		if (!exec)
			ft_exit("ft_strjoin", EXIT_FAILURE);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_tab(s_cmd), ft_free_tab(allpath), exec);
		free(exec);
	}
	return (ft_free_tab(allpath), ft_free_tab(s_cmd), cmd);
}
