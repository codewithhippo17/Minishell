/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:39:19 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:39:19 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

bool	is_op(t_token *token)
{
	if (token && (token->type == DRR || token->type == DLR || token->type == RR
			|| token->type == LR))
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
