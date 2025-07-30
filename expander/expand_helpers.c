/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:44:00 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/18 14:05:05 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_token(t_token **head, t_token *current, t_splited *splited)
{
	t_token	*prev;
	t_token	*next;

	if (!splited->head)
	{
		splited->head = fill_empty_splited();
		splited->tail = splited->head;
	}
	prev = current->prev;
	next = current->next;
	if (prev)
		prev->next = splited->head;
	else
		*head = splited->head;
	if (splited->head)
		splited->head->prev = prev;
	if (splited->tail)
		splited->tail->next = next;
	if (next)
		next->prev = splited->tail;
}
