

#include "minishell.h"


t_token *lexer(const char *input)
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
            append_token(&head, &tail, parse_quoted(&i, input));
        else if (is_operator_start(input[i]))
            append_token(&head, &tail, parse_operator(&i, input));
        else if (input[i] == '$')
            append_token(&head, &tail, parse_variable(&i, input));
        else
            append_token(&head, &tail, parse_word(&i, input));
    }

    return head;
}
