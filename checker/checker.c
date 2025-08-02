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

bool	is_vpipe(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->prev || (token->prev->type == WS && !token->prev->prev))
			return (false);
		if (!token->next || (token->next->type == WS && !token->next->next))
			return (false);
		if (token->next->type == PIPE || (token->next->type == WS
				&& token->next->next->type == PIPE))
			return (false);
	}
	return (true);
}

int checker(t_token **token, t_minishell *minishell)
{
	t_token	*c;
    int res = 0;
	if (check_quote(*token) == false)
		return (1);
	c = *token;
	while (c)
	{
		if (c->type == PIPE)
		{
			if (is_vpipe(c))
				return (1);
		}
		if (is_op(c) == true && (!c->next || is_word(c->next) == false))
			return (1);
		if (c->type == DLR)
			res = ft_heredoc(c, grabdel(c), grabquote(c), minishell);
        if (res != 0)
            return (1);
		c = c->next;
	}
	return (0);
}
