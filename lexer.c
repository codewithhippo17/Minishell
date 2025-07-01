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

#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/*t_token *parse_spaces(int *i, char *input)
{
  t_token *token;
  
  token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
  while (is_space(input[*i]))
  {
    (*i)++;
  }
  token->value = ft_strdup(" ");
  token->quote = NQS;
  token->type = WS;
  token->next = NULL;
  return (token);
}
*/
void fill_token(t_token **token, char *value, t_flag flag, t_quote_type quote)
{
  (*token)->value = ft_strdup(value);
  (*token)->type = flag;
  (*token)->quote = quote;
  (*token)->next = NULL;
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

int main()
{
	int i = 0;

    char *input = ft_strdup("< <<|||>|>jjkhv");
    
	t_token *token = parse_operator(&i, input, input[i]);
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

	else
		printf("LR\n");
}


/*
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
	if (input[*i] == quote){
		(*i)++;
    }
    else if (input[*i] == '\0')
        return (free (token), NULL);           // free all and put the exit status to where it belong
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
			append_token(&head, &tail, parse_operator(&i, input, input[i]));
		else if (input[i] == '$')
			append_token(&head, &tail, parse_variable(&i, input));
		else
			append_token(&head, &tail, parse_word(&i, input));
	}
	return (head);
}*/



