/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 05:50:21 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/21 06:35:13 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flag_join(t_token *c)
{
	if (c->prev == NULL || (c->prev && c->prev->type != WORD))
	{
		if (c->next == NULL || (c->next != NULL && c->next->type != WORD))
			c->join = NJ;
		else if (c->next && c->next->type == WORD)
			c->join = JR;
	}
	else if (c->next == NULL || (c->next && c->next->type != WORD))
	{
		if (c->prev && c->prev->type == WORD)
			c->join = JL;
	}
	else if (c->prev && c->next && c->prev->type == WORD
		&& c->next->type == WORD)
	{
		c->join = J;
	}
}

bool	no_var(char *value)
{
	if (!value || !*value)
		return (false);
	while (*value)
	{
		if (*value == '$')
			return (false);
		value++;
	}
	return (true);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*fill_var_token(char *varname)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = varname;
	token->type = WORD;
	token->quote = NQS;
	token->join = J;
	token->next = NULL;
	token->prev = NULL;
	token->hd = NULL;
	return (token);
}

t_splited   *init_inner(void)
{
    t_splited   *splited;
    splited = malloc(sizeof(t_splited));
    if (!splited)
        return (NULL);
    splited->split = NULL;
    splited->head = NULL;
    splited->tail = NULL;
    splited->len = 0;
    return splited;
}
