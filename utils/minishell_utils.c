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
	char	*result;

	i = 0;
    result = NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j, SCOPE_TEMP);
		if (ft_strcmp(sub, name) == 0)
		{
            if (env[i][j] == '\0' || (env[i][j] == '=' && env[i][j + 1] == '\0'))
            {
                return (ft_strdup("", SCOPE_SESSION));
            }
			result = ft_strdup(env[i] + j + 1, SCOPE_SESSION);
			return (result);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int			i;
	char		*exec;
	char		**allpath;
	char		*path_part;
	char		*result;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':', SCOPE_TEMP);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/", SCOPE_TEMP);
		exec = ft_strjoin(path_part, cmd, SCOPE_TEMP);
		if (access(exec, F_OK) == 0)
		{
			result = ft_strdup(exec, SCOPE_SESSION);
			return (result);
		}
	}
	return (NULL);
}
