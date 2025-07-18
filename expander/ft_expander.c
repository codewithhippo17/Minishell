/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:04:18 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/18 14:01:05 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

static void	flag_join(t_token *c)
{
	if (c->prev && c->prev->type == WS && c->next && c->next->type == WS)
		c->join = NJ;
	else if (c->prev && c->prev->type == WORD && c->next && c->next->type == WORD)
		c->join = J;
	else if (c->prev && c->prev->type == WS && c->next && c->next->type == WORD)
		c->join = JR;
	else if (c->prev && c->prev->type == WORD && c->next && c->next->type == WS)
		c->join = JL;
}


static int	has_var(char *value)
{
	if (!value || !*value)
		return (0);
	while (*value)
	{
		if (*value == '$')
			return (1);
		value++;
	}
	return (0);
}

void	ft_expander(t_token **token, t_minishell *minishell)
{
	t_token	*c;

	c = *token;
	while (c)
	{
		if (!has_var(c->value) || c->quote == SQS)
			flag_join(c);
		else if (has_var(c->value) && c->quote == DQS)
        {
            expander(&c->value, minishell->m_env);
            flag_join(c);
        }
        c = c->next;
	}
}
