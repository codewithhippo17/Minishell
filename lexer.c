/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:06 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/02 17:54:25 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			append_token(&head, &tail, parse_operator(&i, input, input[i]));
		else if (input[i] == '$')
			append_token(&head, &tail, parse_variable(&i, input));
		else
			append_token(&head, &tail, parse_word(&i, input));
	}
	return (head);
}

void print_tokens(t_token *token) {
	while (token) {
		printf("Token: %-10s | Type: %-2d | Quote: %-2d\n", token->value, token->type, token->quote);
		token = token->next;
	}
}

int main(void) {
    
    char *input = ft_strdup("\"echo\" hello | skgbvd$sdfsdhfd>> << |><>>>");

	t_token *tokens = lexer(input);
	print_tokens(tokens);

	// Optional: free memory
	return 0;
}

/*
#include <stdio.h>

int main()
{
	int i = 0;

	char *input = ft_strdup("\"echohello");

	t_token *token = parse_quoted(&i, input, input[i]);
	printf("the original -> %s\n", input);
	printf("the remainer -> %s\n", &input[i]);

	printf("value    -> %s\n", token->value);
	printf("quote    -> ");
	if (token->quote == DQS)
	{
		printf("DQS\n");
	}
	else if (token->quote == NQS)
		printf("NQS\n");
	else if (token->quote == UQS)
		printf("UQS\n");
	else
		printf("SQS\n");
	printf("operator -> ");
	if (token->type == PIPE)
	{
		printf("PIPE\n");
	}
	else if (token->type == DRR)
	{
		printf("DRR\n");
	}

	else if (token->type == DLR)
	{
		printf("DLR\n");
	}
	else if (token->type == RR)
	{
		printf("RR\n");
	}
	else if (token->type == ERROR)
	{
		printf("ERROR\n");
	}

	else
		printf("LR\n");
}*/
