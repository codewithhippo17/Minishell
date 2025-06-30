#include "minishell.h"

int is_space(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

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
