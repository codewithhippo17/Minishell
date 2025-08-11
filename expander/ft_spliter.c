/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:57:19 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:59:03 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*fill_splited(char *snip, t_join join)
{
	t_token	*token;

	token = my_alloc(sizeof(t_token), SCOPE_SESSION);
	token->value = ft_strdup(snip, SCOPE_SESSION);
	token->join = join;
	token->hd = NULL;
	if (ft_memcmp(snip, " ", 1) == 0)
	{
		token->ambg = AMBG;
	}
	else
	{
		token->ambg = OBV;
	}
	token->next = NULL;
	token->prev = NULL;
	token->quote = NQS;
	if (join == NONE)
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
	t_token		*new;

	new = my_alloc(sizeof(t_token), SCOPE_SESSION);
	sp = my_alloc(sizeof(t_splited), SCOPE_SESSION);
	sp->len = 0;
	sp->split = ft_split(word, ' ', SCOPE_TEMP);
	sp->len = ft_len_split(sp->split);
	if (!sp->split)
	{
		fill_token(&(new), NULL, WORD, NQS);
		new->join = J;
		new->ambg = AMBG;
		sp->head = new;
	}
	else if (word && word[0] == '\0')
	{
		fill_token(&(new), "", WORD, NQS);
		new->join = J;
		new->ambg = AMBG;
		sp->head = new;
	}
	else
		sp->head = NULL;
	return (sp->tail = NULL, sp);
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
