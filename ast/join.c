/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:48:41 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 06:22:36 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
 * here a function that loop the hole linked list of tokens
 * and join the value of the tokens
 * -if the current is NONE or NJ skip the current
 * -if the current is J || JR && JL
	|| J then join the current->value with current->next->value and put it in current->value
 * and inherit the join flag from curent->next into the current
 * */

void	ft_join_tokens(t_token **token)
{
	t_token	*current;

    current = *token;
    while (current)
	{
		if (current->next && (current->join == J || current->join == JR)
			&& (current->next->join == J || current->next->join == JL))
        {
            current->value = ft_strjoin(current->value, current->next->value);
            current->join = current->next->join;
            if (current->next->next != NULL)
                current->next->next->prev = current;

            current->next = current->next->next;
        }
        else
            current = current->next;
	}
}
