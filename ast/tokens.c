/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 03:05:20 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:51:35 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_red(t_token *c)
{
	return (c->type == RR || c->type == LR || c->type == DRR);
}

void	delete(t_token **head, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
		return ;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (*head == tmp)
		*head = tmp->next;
	*token = (*token)->next;
}

/*
 * NOTE: need to take a look on how this greper should functionate
 * */

t_token	*grep_tokens(t_token **tokens)
{
	t_token	*c;
	t_token	*cmd;

	c = *tokens;
	cmd = *tokens;
	while (c)
	{
		if (c->type == PIPE)
		{
			c->prev->next = NULL;
			cmd = *tokens;
			return (c->prev = NULL, delete (tokens, &(c)), *tokens = c, cmd);
		}
		if (c->type == HEREDOC || c->type == WS)
			delete (tokens, &c);
		else if (is_red(c))
		{
			delete (tokens, &c);
			if (c->type == WS)
				delete (tokens, &c);
			if (c->ambg == OBV)
				delete (tokens, &c);
			else
			{
				while (c && c->ambg == AMBG)
					delete (tokens, &c);
			}
		}
		else
			c = c->next;
	}
	return (cmd = *tokens, *tokens = c, cmd);
}
