/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 09:04:18 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/18 14:01:05 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>
#include <stdio.h>

static void	flag_join(t_token *c)
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

static bool	no_var(char *value)
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

char *char_to_str(char c)
{
    char *str = malloc(2);
    if (!str)
        return NULL;
    str[0] = c;
    str[1] = '\0';
    return str;
}

t_token	*nonvar_parser(char *str, int *i)
{
	char	*tmp;
    int idx;

    idx = 0;
    if (!str || !str[idx])
        return NULL;
    tmp = ft_strdup("");
    while (str[idx])
    {
        if (str[idx] == '$')
        {
            if (str[idx] && str[idx + 1] && str[idx + 1] == '?')
            {
                tmp = ft_strjoin(tmp, ft_strdup("127"));
                idx += 2; // Skip the $? part
            }
            else if (str[*i] && ft_isdigit(str[*i + 1]))
            {
                tmp = ft_strjoin(tmp, ft_substr(str, *i, 2));
                idx++;
            }
            else
                break; // Stop if we encounter a variable
        }
        else
        {
            tmp = ft_strjoin(tmp, char_to_str(str[idx]));
        }
        idx++;
    }
    t_token *token = malloc(sizeof(t_token));
    token->value = tmp;
    token->type = WORD;
    token->quote = NQS;
    token->join = J;
    token->next = NULL;
    token->prev = NULL;
    token->hd = NULL;
    *i += idx; // Update index to skip processed characters
    return token;
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
    *i += len + 1; // Move index past the variable name
    return (varname);
}

void	ft_exspliter(t_token **token, char *str, int idx,
		t_minishell *minishell)
{
    t_splited   *splited;
    t_token     *inner_head;
    t_token     *inner_tail;
    int         i;
    t_token     *c;

    i = 0;
	c = *token;
	inner_head = NULL;
	inner_tail = NULL;
	while (idx-- > 0)
		c = c->next;
	while (str[i])
	{
		if (str[i] != '$')
		{
			append_token(&inner_head, &inner_tail, nonvar_parser(&str[i], &i));
		}
		else
		{
			splited = ft_spliter(my_getenv(get_varname(&str[i], &i),minishell->m_env));
            append_token(&inner_head, &inner_tail, splited->head);
            inner_tail = splited->tail;
        }
	}
    print_tokens(inner_head);
}

void	ft_expander(t_token **token, t_minishell *minishell)
{
	t_token	*c;
	int		idx;

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
			ft_exspliter(token, c->value, idx, minishell);
		}
		idx++;
		c = c->next;
	}
}
