/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 03:55:40 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/02 04:19:57 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_collected(t_collect **head, t_collect *prev,
		t_collect **to_delete)
{
	t_collect	*tmp;

	tmp = *to_delete;
	if (!tmp)
		return ;
    if (!prev)
        *head = tmp->next;
    else
    {
        prev->next = tmp->next;
    }
    *to_delete = tmp->next;
    free(tmp);
}

void	append_collected(t_collect **head, t_collect **tail, t_collect *new_col)
{
	if (!new_col)
		return ;
	if (!*head)
	{
		*head = new_col;
		*tail = new_col;
	}
	else
	{
		(*tail)->next = new_col;
		*tail = new_col;
	}
}

