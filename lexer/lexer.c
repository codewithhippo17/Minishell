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

#include "../minishell.h"

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

void	print_tokens(t_token *token)
{
	t_token	*curr = token;
    t_token *hhh = NULL;


	printf("Lexer Output:\n    ");
	while (curr)
	{
		printf("[%s]", curr->value);
		if (curr->next)
        {
    		printf("->");
        }

            hhh = curr;
		curr = curr->next;
	}
    printf("\nhhhhhhhhh\n");
    while (hhh)
    {
		printf("[%s]", hhh->value);
		if (hhh->prev)
			printf("<-");
		hhh = hhh->prev;
    }
	printf("\n\n");

	// Summary
	printf("Summary:\n");
	while (token)
	{
		const char *type_str;
		const char *quote_str;

		// Token type string representation
		switch (token->type)
		{
			case CMD: type_str = "CMD"; break;
			case ARG: type_str = "ARG"; break;
			case VAR: type_str = "VAR"; break;
			case PIPE: type_str = "PIPE"; break;
			case RR: type_str = "RR"; break;
			case DRR: type_str = "DRR"; break;
			case LR: type_str = "LR"; break;
			case DLR: type_str = "DLR"; break;
			case ES: type_str = "ES"; break;
            case WS: type_str = "WS"; break;
			case WORD: type_str = "WORD"; break;
			case ERROR: type_str = "ERROR"; break;
		}

		// Quote type string representation
		switch (token->quote)
		{
			case NQS: quote_str = "NQS"; break;
			case SQS: quote_str = "SQS"; break;
			case DQS: quote_str = "DQS"; break;
			case UQS: quote_str = "UQS"; break;
		}

		printf("    [%-12s] → %-10s | %s\n", token->value, type_str, quote_str);
		token = token->next;
	}
}


int	main(int argc, char *argv[], char **env)
{
    char *input;
	while (argc == 1 && argv)
	{
		input = readline("minishell$");
        t_token *tokens = lexer(input);
	    print_tokens(tokens);
    }

	return (EXIT_SUCCESS);
}
