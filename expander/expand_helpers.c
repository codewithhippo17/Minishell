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


static int	get_var_len(const char *str)
{
    int len = 0;

    while (str[len] && is_var_char(str[len]))
        len++;
    return len;
}

static int	getnon_var_len(const char *str)
{
    int len = 0;

    while (str[len] && str[len] != '$')
        len++;
    return len;
}


void	expander(char **string, char **env)
{
    char    *expanded;
    char    *var_name;
    char    *var_value;
    char    *non_var_part;
    int     i = 0;
    int     len;

    expanded = ft_strdup("");
    while ((*string)[i])
    {
        if ((*string)[i] == '$' && is_var_char((*string)[i + 1]))
        {
            len = get_var_len((*string) + i + 1);
            var_name = ft_substr(*string, i + 1, len);
            var_value = my_getenv(var_name, env);
            expanded = ft_join(expanded, var_value ? var_value : "");
            i += len + 1;  // +1 for the '$'
        }
        else
        {
            len = getnon_var_len((*string) + i);
            non_var_part = ft_substr(*string, i, len);
            expanded = ft_join(expanded, non_var_part);
            i += len;
        }
    }
    free(*string);
    *string = expanded;
}

