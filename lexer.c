

#include "minishell.h"
#include <stdlib.h>


int is_quote(char c)
{
    if (c == 34 || c == 39)
        return (1);
    return (0);
}

int is_operator_start(char c)
{
    if (c == '|' || c == '<' || c == '>')
        return (1);
    return (0);
}

char	*ft_strndup(char *s, int len)
{
	char	*tmp;
	int 	i;

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

t_token *parse_quoted(int *i, char *input, char quote)
{
    t_token *token;
    int     start;
    int     len;

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


t_token *lexer(char *input)
{
    int i = 0;
    t_token *head = NULL;
    t_token *tail = NULL;

    while (input[i])
    {
        skip_whitespace(&i, input);
        if (input[i] == '\0')
            break;
        if (is_quote(input[i]))
            append_token(&head, &tail, parse_quoted(&i, input, input[i]));
        else if (is_operator_start(input[i]))
            append_token(&head, &tail, parse_operator(&i, input));
        else if (input[i] == '$')
            append_token(&head, &tail, parse_variable(&i, input));
        else
            append_token(&head, &tail, parse_word(&i, input));
    }
    return head;
}

int main()
{
    int i = 0;
    
    t_token *token = parse_quoted(&i, "echo");
    printf("%s\n", token->value);
    if (token->quote == DQS) {
        printf("DQS\n");
    }
    else
        printf("SQS\n"); 
}

