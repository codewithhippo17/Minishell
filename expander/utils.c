/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:07:32 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 00:07:32 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_joinable(t_token *c)
{
	if (!c->next)
		return (true);
	if ((c->join == J || c->join == JR) && (c->next->join == JL
			|| c->next->join == J))
		return (true);
	return (false);
}

void	flag_ambg(t_token *token)
{
	t_token	*c;
	bool	is_ambg;

	is_ambg = false;
	c = token;
	if (!c)
		return ;
	while (c && is_ambg == false)
	{
		if (is_joinable(c) == false)
			is_ambg = true;
		c = c->next;
	}
	if (is_ambg == true)
	{
		c = token;
		while (c)
		{
			c->ambg = AMBG;
			c = c->next;
		}
	}
}

int	is_var_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}

char	*get_varname(char *str, int *i)
{
	int		len;
	char	*varname;

	len = get_var_len(&str[1]);
	if (len == 0)
		return (NULL);
	varname = malloc(len + 1);
	if (!varname)
		return (NULL);
	ft_strlcpy(varname, &str[1], len + 1);
	*i += len + 1;
	return (varname);
}
