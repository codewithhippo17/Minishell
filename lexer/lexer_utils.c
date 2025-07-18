/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 18:08:48 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/02 18:14:38 by ehamza           ###   ########.fr       */
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
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (input[*i] && !is_space(input[*i]) && !is_quote(input[*i])
		&& !is_operator_start(input[*i]))
	{
		(*i)++;
		len++;
	}
	token->value = ft_strndup(&input[start], len);
	token->type = WORD;
	token->quote = NQS;
	token->join = NJ;
	token->hd = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*parse_spaces(int *i, char *input)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	while (is_space(input[*i]))
	{
		(*i)++;
	}
	token->value = ft_strdup(" ");
	token->type = WS;
	token->quote = NQS;
	token->join = NJ;
	token->hd = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*parse_operator(int *i, char *input, char op)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
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
		fill_token(&token, ft_strndup(&input[start], len), WORD, DQS);
	else
		fill_token(&token, ft_strndup(&input[start], len), WORD, SQS);
	return (token->prev = NULL, token->next = NULL, token);
}
