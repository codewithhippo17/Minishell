/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:26:19 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/04 20:57:30 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

bool	is_op(t_token *token)
{
	if (token && (token->type == DRR || token->type == DLR
			|| token->type == RR || token->type == LR))
	{
		return (true);
	}
	return (false);
}

bool	is_word(t_token *token)
{
	if (token->type == WORD)
	{
		return (true);
	}
    else if (token->next && token->type == WS && token->next->type == WORD)
    {
        return (true);
    }
	return (false);
}


