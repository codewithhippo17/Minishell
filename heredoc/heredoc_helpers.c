/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:50:54 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/15 11:03:02 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"

t_heredoc	*init_heredoc(void)
{
	t_heredoc	*new;

	new = my_alloc(sizeof(t_heredoc), SCOPE_SESSION);
	new->fd = -1;
	new->tmp_fd = -1;
	new->filename = NULL;
	new->line = NULL;
	new->del = NULL;
	return (new);
}
