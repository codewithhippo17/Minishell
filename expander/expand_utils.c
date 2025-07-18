/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:58:50 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/18 14:36:52 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

bool	last_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (is_space(str[i - 1]));
}

int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	get_var_len(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && is_var_char(str[len]))
		len++;
	return (len);
}

int	getnon_var_len(const char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '$')
		len++;
	return (len);
}
