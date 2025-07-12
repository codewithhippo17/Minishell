/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:44:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/12 14:44:01 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	expander(char **string, char **env)
{
	char	*src = *string;
	char	*result = ft_strdup("");  // Will build the new string here
	int		i = 0;

	while (src[i])
	{
		if (src[i] == '$')
		{
			i++;
			int	start = i;
			while (is_var_char(src[i]))
				i++;
			char	*var_name = ft_substr(src, start, i - start);
			char	*var_value = my_getenv(var_name, env);
			free(var_name);
			if (var_value)
			{
				char *tmp = ft_strjoin(result, var_value);
				free(result);
				result = tmp;
			}
		}
		else
		{
			int start = i;
			while (src[i] && src[i] != '$')
				i++;
			char *chunk = ft_substr(src, start, i - start);
			char *tmp = ft_strjoin(result, chunk);
			free(result);
			free(chunk);
			result = tmp;
		}
	}
	free(*string);
	*string = result;
}
