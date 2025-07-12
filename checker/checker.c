/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:24:01 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/03 00:24:02 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"
#include "../minishell.h"

bool    checker(t_token **token, t_minishell *minishell)
{
    if (check_quote(*token) == false)
        return (false);
    t_token *current;

    current = *token;
    while (current)
    {
        if (current->type == PIPE)
        {
            if (!current->prev || (current->prev->type == WS && !current->prev->prev))
                return (false);
            if (!current->next || (current->next->type == WS && !current->next->next))
                return (false);
            if (current->next->type == PIPE || (current->next->type == WS && current->next->next->type == PIPE))
                return (false);
        }
        if (is_op(current) == true && (!current->next || is_word(current->next) == false))
            return (false);
        if (current->type == DLR)
            ft_heredoc(current, grabdel(current), grabquote(current), minishell);
        current = current->next;
    }
    return (true);
}
