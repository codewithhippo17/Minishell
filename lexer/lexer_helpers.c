/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:44:01 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:44:01 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_token(t_token **token, char *value, t_flag flag, t_quote quote)
{
    if (value)
	    (*token)->value = ft_strdup(value, SCOPE_SESSION);
    else
        (*token)->value = NULL;
    (*token)->type = flag;
	(*token)->quote = quote;
	(*token)->join = NJ;
	(*token)->ambg = OBV;
	(*token)->hd = NULL;
	(*token)->next = NULL;
	(*token)->prev = NULL;
}

void	append_token(t_token **head, t_token **tail, t_token *new_token)
{
	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		*tail = new_token;
	}
	else
	{
		(*tail)->next = new_token;
		new_token->prev = *tail;
		*tail = new_token;
	}
}
