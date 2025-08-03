/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:18:41 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/15 11:00:44 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"
#include <stdlib.h>

int	ft_heredoc(t_token *token, char *del, t_quote quote, t_minishell *minishell)
{
	t_heredoc	*hd;
	char		*r;

	hd = init_heredoc();
	r = ft_random();
	if (!r)
		return (collector_cleanup(SCOPE_SESSION), collector_cleanup(SCOPE_TEMP),
			1);
	hd->del = del;
	hd->quote = quote;
	hd->filename = ft_strjoin("/tmp/heredoc", r, SCOPE_SESSION);
	if (heredoc(hd, minishell) == 1)
	{
		return (1);
	}
	token->hd = hd;
	token->type = HEREDOC;
	if (token->next->type == WORD)
		token->next = token->next->next;
	else
	{
		token->next = token->next->next->next;
	}
	return (0);
}
