/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:44:08 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 19:12:18 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*parse_word(int *i, char *input)
{
	t_token	*token;
	int		start;
	int		len;

	start = *i;
	len = 0;
	token = my_alloc(sizeof(t_token), SCOPE_SESSION);
	while (input[*i] && !is_space(input[*i]) && !is_quote(input[*i])
		&& !is_operator_start(input[*i]))
	{
		(*i)++;
		len++;
	}
	token->value = ft_strndup(&input[start], len, SCOPE_SESSION);
	token->type = WORD;
	token->quote = NQS;
	token->join = NJ;
	token->ambg = OBV;
	token->hd = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*parse_spaces(int *i, char *input)
{
	t_token	*token;

	token = my_alloc(sizeof(t_token), SCOPE_SESSION);
	while (is_space(input[*i]))
	{
		(*i)++;
	}
	token->value = ft_strdup(" ", SCOPE_SESSION);
	token->type = WS;
	token->quote = NQS;
	token->join = NJ;
	token->ambg = OBV;
	token->hd = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*parse_operator(int *i, char *input, char op)
{
	t_token	*token;

	token = my_alloc(sizeof(t_token), SCOPE_SESSION);
	if (op == '|')
		fill_token(&token, "|", PIPE, NQS);
	else if (op == '>' && input[*i + 1] == '>')
	{
		fill_token(&token, ">>", DRR, NQS);
		(*i)++;
	}
	else if (op == '>')
		fill_token(&token, ">", RR, NQS);
	else if (op == '<' && input[*i + 1] == '<')
	{
		fill_token(&token, "<<", DLR, NQS);
		(*i)++;
	}
	else if (op == '<')
		fill_token(&token, "<", LR, NQS);
	(*i)++;
	return (token);
}

t_token	*parse_quoted(int *i, char *input, char quote)
{
	t_token	*token;
	int		start;
	int		len;

	len = 0;
	start = ++(*i);
	token = my_alloc(sizeof(t_token), SCOPE_SESSION);
	while (input[*i] && input[*i] != quote)
	{
		(*i)++;
		len++;
	}
	if (input[*i] == quote)
		(*i)++;
	else if (input[*i] == '\0')
		return (fill_token(&token, &input[start], ERROR, UQS), token);
	if (quote == '"')
		fill_token(&token, ft_strndup(&input[start], len, SCOPE_SESSION), WORD,
			DQS);
	else
		fill_token(&token, ft_strndup(&input[start], len, SCOPE_SESSION), WORD,
			SQS);
	token->ambg = OBV;
	token->join = NJ;
	return (token->prev = NULL, token->next = NULL, token);
}
