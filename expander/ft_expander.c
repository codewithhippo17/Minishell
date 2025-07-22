/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:04:18 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 06:45:55 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

t_token	*nonvar_parser(char *str, int *i)
{
	char	*tmp;
	int		idx;
	t_token	*token;

	idx = 0;
	if (!str || !str[idx])
		return (NULL);
	tmp = ft_strdup("");
	while (str[idx])
	{
		if (str[idx] == '$')
		{
			if (str[*i] && ft_isdigit(str[*i + 1]))
			{
				tmp = ft_strjoin(tmp, ft_substr(str, *i, 2));
				idx++;
			}
			else
				break ;
		}
		else
			tmp = ft_strjoin(tmp, char_to_str(str[idx]));
		idx++;
	}
	return (*i += idx, token = fill_var_token(tmp), token);
}

char	*get_varname(char *str, int *i)
{
	int		len;
	char	*varname;

	len = get_var_len(&str[1]);
	if (len == 0)
		return (NULL);
	varname = malloc(len + 1);
	if (!varname)
		return (NULL);
	ft_strlcpy(varname, &str[1], len + 1);
	*i += len + 1;
	return (varname);
}

t_splited	*ft_exspliter(t_token **token, char *str, int idx,
		t_minishell *minishell)
{
	t_splited	*splited;
	t_splited	*tmp;
	int			i;
	t_token		*c;

	i = 0;
	c = *token;
	tmp = init_inner();
	while (idx-- > 0)
		c = c->next;
	while (str[i])
	{
		if (str[i] != '$')
			append_token(&tmp->head, &tmp->tail, nonvar_parser(&str[i], &i));
		else
		{
			splited = ft_spliter(my_getenv(get_varname(&str[i], &i),
						minishell->m_env));
			append_token(&tmp->head, &tmp->tail, splited->head);
			if (splited->tail)
				tmp->tail = splited->tail;
		}
	}
	flag_ambg(tmp->head);
	return (tmp);
}

t_token	*fill_empty_splited(void)
{
    t_token	*token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->join = NJ;
    token->ambg = AMBG;
    token->hd = NULL;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}


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

void	ft_expander(t_token **token, t_minishell *minishell)
{
	t_token		*c;
	t_splited	*splited;
	int			idx;

	idx = 0;
	c = *token;
	while (c)
	{
		if (c->type != WORD)
			c->join = NONE;
		else if (no_var(c->value) || c->quote == SQS)
			flag_join(c);
		else if (!no_var(c->value) && c->quote == DQS)
		{
			expander(&c->value, minishell->m_env);
			flag_join(c);
		}
		else if (!no_var(c->value))
		{
			splited = ft_exspliter(token, c->value, idx, minishell);
			insert_token(token, c, splited);
		}
		idx++;
		c = c->next;
	}
}
