/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:40:40 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 19:00:28 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
