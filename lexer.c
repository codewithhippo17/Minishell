/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:06 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/01 14:12:34 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*ft_strndup(char *s, int len)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)malloc(len + 1);
	if (!tmp)
		return (NULL);
	while (s[i] && i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
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
	if (input[*i])
		(*i)++;
	token->value = ft_strndup(&input[start], len);
	token->type = ARG;
	if (quote == '"')
		token->quote = DQS;
	else
		token->quote = SQS;
	token->next = NULL;
	return (token);
}

t_token	*lexer(char *input)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (input[i])
	{
		if (is_space(input[i]))
			append_token(&head, &tail, parse_spaces(&i, input));
		else if (is_quote(input[i]))
			append_token(&head, &tail, parse_quoted(&i, input, input[i]));
		else if (is_operator_start(input[i]))
			append_token(&head, &tail, parse_operator(&i, input));
		else if (input[i] == '$')
			append_token(&head, &tail, parse_variable(&i, input));
		else
			append_token(&head, &tail, parse_word(&i, input));
	}
	return (head);
}

/*
int main()
{
	int i = 0;

	t_token *token = parse_quoted(&i, "echo", '"');
	printf("%s\n", token->value);
	if (token->quote == DQS)
	{
		printf("DQS\n");
	}
	else
		printf("SQS\n");
}*/
