/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:42 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/06 19:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j, SCOPE_TEMP);
		if (ft_strcmp(sub, name) == 0)
		{
			return (env[i] + j + 1);
		}
		i++;
	}
    collector_cleanup(SCOPE_TEMP);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int			i;
	char		*exec;
	char		**allpath;
	char		*path_part;
	struct stat	stats;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':', SCOPE_TEMP);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/", SCOPE_TEMP);
		exec = ft_strjoin(path_part, cmd, SCOPE_TEMP);
		if (access(exec, F_OK) == 0)
		{
			stat(exec, &stats);
			if (S_ISDIR(stats.st_mode))
				continue ;
			return (ft_strdup(exec, SCOPE_SESSION));
		}
        collector_cleanup(SCOPE_TEMP);
	}
	return (NULL);
}
