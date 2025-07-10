/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:18:41 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/09 17:18:42 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"
#include "../minishell.h"

void ft_heredoc(t_token *token, char *delimiter, t_quote quote)
{
    heredoc_t *hd;
    int result;

    hd = init_heredoc();
    if (!hd)
        return ;
    hd->del = ft_strdup(delimiter);
    hd->quote = quote;
    if (!hd->del)
    {
        free_heredoc(hd);
        return ;
    }
    hd->filename = ft_strjoin("/tmp/heredoc", ft_random());
    if (!hd->filename)
    {
        free_heredoc(hd);
        return ;
    }
    result = heredoc(hd);
    if (result == -1)
    {
        free_heredoc(hd);
        return ;
    }
    token->hd = hd;
}



