/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:34:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/04 22:34:04 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"
#include "../minishell.h"

bool	check_quote(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->quote == UQS)
			return (false);
		current = current->next;
	}
	return (true);
}

char	*grabdel(t_token *token)
{
	char	*delimiter;

	if (token->next->type == WORD)
	{
		delimiter = token->next->value;
		if (!delimiter)
			return (NULL);
	}
	else
	{
		delimiter = token->next->next->value;
		if (!delimiter)
			return (NULL);
	}
	return (delimiter);
}

t_quote	grabquote(t_token *token)
{
	t_quote	quote;

	if (token->next->type == WORD)
	{
		quote = token->next->quote;
	}
	else
	{
		quote = token->next->next->quote;
	}
	return (quote);
}
