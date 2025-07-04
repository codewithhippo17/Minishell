/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:26:19 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/03 00:26:20 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

bool is_op(t_token *token)
{
    if (token->type == PIPE || token->type == DLR || token->type == DRR || token->type == RR || token->type == LR)
    {
        return (true);
    }
}
