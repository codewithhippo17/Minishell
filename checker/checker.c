/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:24:01 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/15 11:05:50 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"
#include "../minishell.h"

bool	checker(t_token **token, t_minishell *minishell)
{
	t_token	*c;

	if (check_quote(*token) == false)
		return (false);
	c = *token;
	while (c)
	{
		if (c->type == PIPE)
		{
			if (!c->prev || (c->prev->type == WS && !c->prev->prev))
				return (false);
			if (!c->next || (c->next->type == WS && !c->next->next))
				return (false);
			if (c->next->type == PIPE || (c->next->type == WS
					&& c->next->next->type == PIPE))
				return (false);
		}
		if (is_op(c) == true && (!c->next || is_word(c->next) == false))
			return (false);
		if (c->type == DLR)
			ft_heredoc(c, grabdel(c), grabquote(c), minishell);
		c = c->next;
	}
	return (true);
}
