/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:44:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/18 14:05:05 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	expander(char **string, char **env)
{
	char	*expanded;
	char	*var_name;
	char	*var_value;
	char	*non_var_part;
	int		i;
	int		len;

	i = 0;
	expanded = ft_strdup("");
	while ((*string)[i])
	{
		if ((*string)[i] == '$' && is_var_char((*string)[i + 1]))
		{
			len = get_var_len((*string) + i + 1);
			if (len > 0)
			{
				var_name = ft_substr((*string), i + 1, len);
				if (*var_name)
					var_value = my_getenv(var_name, env);
				if (var_value)
					expanded = ft_strjoin(expanded, var_value);
				i += len + 1;
			}
		}
		else if ((*string)[i] == '$' && !is_var_char((*string)[i + 1]))
		{
			if ((*string)[i + 1] == '?')
			{
				expanded = ft_strjoin(expanded, ft_strdup("127"));
				i++;
			}
			else
				expanded = ft_strjoin(expanded, ft_strdup("$"));
			i++;
		}
		else
		{
			len = getnon_var_len((*string) + i);
			non_var_part = ft_substr(*string, i, len);
			expanded = ft_strjoin(expanded, non_var_part);
			i += len;
		}
	}
	free(*string);
	*string = expanded;
}
