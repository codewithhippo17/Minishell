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

int ft_heredoc(t_token *token, char *del, t_quote quote,
		t_minishell *minishell)
{
	t_heredoc	*hd;

	hd = init_heredoc();
	hd->del = ft_strdup(del);
	hd->quote = quote;
	hd->filename = ft_strjoin("/tmp/heredoc", ft_random());
    if (heredoc(hd, minishell) == 1)
    {
        return 1;
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
