/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 05:00:21 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 06:19:26 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	function loop to traverse the token linked list and grab
	all the redirection tokens
	and create a new linked list of redirection tokens.

 * typedef struct s_red
 * {
 *      int					fd;
 *      char				*path;
 *      t_flag				type;
 *      t_ambg				ambg;
 *  }						t_red;

	be aware

*/

t_red	*red(int fd, t_flag type, t_ambg ambg, char *path)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	red->fd = fd;
	red->path = path;
	red->type = type;
	red->ambg = ambg;
	red->next = NULL;
	return (red);
}

static void	append_red(t_red **head, t_red **tail, t_red *new_red)
{
	if (!new_red)
		return ;
	if (!*head)
	{
		*head = new_red;
		*tail = new_red;
	}
	else
	{
		(*tail)->next = new_red;
		*tail = new_red;
	}
}

t_red	*sub_red(t_token *token)
{
	t_red	*head;
	t_red	*tail;
	t_token	*c;

	head = NULL;
	tail = NULL;
	c = token;
	while (c && c->type != PIPE)
	{
		if (c->type == LR || c->type == DRR || c->type == RR)
		{
			if (c->next->ambg == AMBG || (c->next->type == WS
					&& c->next->next->ambg == AMBG))
				append_red(&head, &tail, red(-1, c->type, AMBG, NULL));
			else if (c->next->type != WS)
				append_red(&head, &tail, red(-1, c->type, OBV, c->next->value));
			else if (c->next->type == WS)
				append_red(&head, &tail, red(-1, c->type, OBV,
						c->next->next->value));
		}
		else if (c->type == HEREDOC)
			append_red(&head, &tail, red(c->hd->fd, c->type, OBV, NULL));
		c = c->next;
	}
	return (head);
}
