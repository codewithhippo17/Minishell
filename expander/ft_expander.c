/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:04:18 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/15 10:11:43 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		i++;
	}
	return (i);
}

bool	last_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (is_space(str[i - 1]));
}

t_splited	*init_splited(void)
{
	t_splited	*sp;

	sp = malloc(sizeof(t_splited));
	if (!sp)
		return (NULL);
	sp->len = 0;
	sp->head = NULL;
	sp->tail = NULL;
	sp->split = NULL;
	return (sp);
}

t_token	*fill_splited(char *snip, t_join join)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(snip);
	token->join = join;
	token->hd = NULL;
	token->next = NULL;
	token->prev = NULL;
	token->quote = NQS;
	if (join == NJ)
		token->type = ARG;
	else
		token->type = WORD;
	return (token);
}

t_splited	*ft_spliter(char *word)
{
	t_splited	*sp;
	int			i;

	i = -1;
	sp = init_splited();
	sp->split = ft_split(word, ' ');
	sp->len = ft_len_split(sp->split);
	while (sp->split[++i])
	{
		if (i == 0 && is_space(word[0]) && ((last_space(word) && sp->len == 1)
				|| sp->len > 1))
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], NJ));
		else if (i < sp->len - 1 && i > 0)
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], NJ));
		else if (i == sp->len - 1 && sp->len > 1 && last_space(word))
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], NJ));
		else if (sp->len == 1 && !is_space(word[0]) && !last_space(word))
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], J));
		else if (i == 0 && !is_space(word[0]))
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], JL));
		else if (!last_space(word) && i == sp->len - 1)
			append_token(&sp->head, &sp->tail, fill_splited(sp->split[i], JR));
	}
	return (sp);
}
