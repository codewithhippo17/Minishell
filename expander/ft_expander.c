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
#include <stdbool.h>

static void	flag_join(t_token *c)
{
    if (c->prev == NULL || c->prev->type != WORD)
    {
        if (c->next == NULL || c->next->type != WORD)
            c->join = NJ;
        else if (c->next && c->next->type == WORD)
            c->join = JR;
    }
    else if (c->next == NULL || c->next->type != WORD)
    {
        if (c->prev && c->prev->type == WORD)
            c->join = JL;
    }
    else if (c->prev && c->next && c->prev->type == WORD && c->next->type == WORD)
    {
        c->join = J;
    }
}

static bool has_var(char *value)
{
	if (!value || !*value)
		return (false);
	while (*value)
	{
		if (*value == '$')
			return (false);
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
        if (c->type == WS)
            c->join = NONE;
        else if (!has_var(c->value) || c->quote == SQS)
			flag_join(c);
		else if (has_var(c->value) && c->quote == DQS)
		{
			expander(&c->value, minishell->m_env);
			flag_join(c);
		}
		c = c->next;
	}
}
