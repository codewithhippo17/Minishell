/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:20:05 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/02 18:20:08 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_token(t_token **token, char *value, t_flag flag, t_quote quote)
{
	(*token)->value = ft_strdup(value);
	(*token)->type = flag;
	(*token)->quote = quote;
    (*token)->join = NJ;
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
