/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:57:19 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/21 06:13:37 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*fill_splited(char *snip, t_join join)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(snip);
	token->join = join;
	token->hd = NULL;
	token->ambg = OBVIOUS;
	token->next = NULL;
	token->prev = NULL;
	token->quote = NQS;
	if (join == NJ)
		token->type = ARG;
	else if (join == NONE)
		token->type = WS;
	else
		token->type = WORD;
	return (token);
}

bool	is_all_space(char *word)
{
	if (!word || !*word)
		return (false);
	while (*word)
	{
		if (*word != ' ')
			return (false);
		word++;
	}
	return (true);
}

static t_splited	*init_splited(char *word)
{
	t_splited	*sp;

	sp = malloc(sizeof(t_splited));
	if (!sp)
		return (NULL);
	sp->len = 0;
	sp->split = ft_split(word, ' ');
	sp->len = ft_len_split(sp->split);
	sp->head = NULL;
	sp->tail = NULL;
	return (sp);
}

t_splited	*ft_spliter(char *word)
{
	t_splited	*sp;
	int			i;

	i = -1;
	sp = init_splited(word);
	if (is_all_space(word))
		return (append_token(&sp->head, &sp->tail, fill_splited(" ", NONE)),
			sp);
	while (sp->split && sp->split[++i])
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
