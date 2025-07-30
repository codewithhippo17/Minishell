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

t_token	*nonvar_parser(char *str, int *i, t_minishell *minishell)
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
        if (str[idx] == '$' && str[idx + 1] == '?')
        {
			tmp = ft_strjoin(tmp, ft_itoa(minishell->status));
            idx += 2;
        }
        else if (str[idx] == '$' && str[idx + 1] && !is_var_start(str[idx + 1]))
			tmp = ft_strjoin(tmp, char_to_str(str[idx++]));
		else if (str[idx] == '$' && !str[idx + 1])
			tmp = ft_strjoin(tmp, char_to_str(str[idx++]));
		else if (str[idx] && str[idx] != '$')
			tmp = ft_strjoin(tmp, char_to_str(str[idx++]));
		else
			break ;
	}
	return (*i += idx, token = fill_var_token(tmp), token);
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
		if (str[i] != '$' || (str[i] == '$' && !is_var_start(str[i + 1])))
			append_token(&tmp->head, &tmp->tail, nonvar_parser(&str[i], &i,
					minishell));
		else
		{
			splited = ft_spliter(my_getenv(get_varname(&str[i], &i),
						minishell->s_env));
			append_token(&tmp->head, &tmp->tail, splited->head);
			if (splited->tail)
				tmp->tail = splited->tail;
		}
	}
	flag_ambg(tmp->head);
	return (tmp);
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
