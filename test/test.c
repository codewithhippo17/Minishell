#include "../minishell.h"

const char *flag_to_string(t_flag flag)
{
    static const char *flag_names[] = {
        "WORD", "CMD", "ARG", "WS", "PIPE",
        "LR", "RR", "DLR", "DRR", "HEREDOC",
        "VAR", "ES", "ERROR"
    };

    if (flag < 0 || flag > ERROR)
        return "UNKNOWN";
    return flag_names[flag];
}

const char *quote_to_string(t_quote quote)
{
    static const char *flag_names[] = {
        	"NQS", "SQS", "DQS", "UQS"
    };
        if (quote < 0 || quote > UQS)
            return "UNKNOWN";
    return flag_names[quote];
}

const char *ambg_to_string(t_ambg quote) 
{ 
    static const char *flag_names[] = {
        	"AMBG", "OBVIOUS"
    };
        if (quote < 0 || quote > OBV)
            return "UNKNOWN";
    return flag_names[quote];
}


const char *join_to_string(t_join join)
{
    static const char *flag_names[] = {
        	"J", "JL", "JR", "NJ" , "NONE"
    };
        if (join < 0 || join > NONE)
            return "UNKNOWN";
    return flag_names[join];
}

void print_tokens(t_token *token, int nb)
{
    t_token *curr = token;
    static int i;
    if (nb == 0)
        i = 0;

    printf("\033[32m");
    printf("CMD : %d\n    ->", ++i);
    printf("\033[0m");
    while (curr)
    {
        if (curr->type == PIPE)
        {
            printf("\n");
            curr = curr->next;
            continue ;
        }
        if (curr->value)
            printf("[\e[1;34m{\"%s\"}\e[0m: \033[31m%s-%s-%s\033[0m]", curr->value, flag_to_string(curr->type), join_to_string(curr->join), ambg_to_string(curr->ambg));
        else if (!curr->value)
            printf("[\e[1;34m{\"null\"}\e[0m: \033[31m %s-%s-%s\033[0m]", flag_to_string(curr->type), join_to_string(curr->join), ambg_to_string(curr->ambg));
        if (curr->next)
            printf("\033[32;1m🠒\033[0m");
        curr = curr->next;
    }
    printf("\n\n");
}

void print_redirections(t_red *red)
{
    t_red *curr = red;

    printf("Redirections:\n");
    while (curr)
    {
        printf("[\e[1;34m{\"path: %s\"}\e[0m: \033[31m%s-%s fd: %d\033[0m]", curr->path, flag_to_string(curr->type), ambg_to_string(curr->ambg), curr->fd);
        if (curr->next)
            printf("\033[32;1m🠒\033[0m");
        curr = curr->next;
    }
    printf("\n\n");
}

void print_script(t_script *script)
{
    t_script *current;

    int i = 0;
    current = script;
    while (current)
    {
        print_tokens(current->cmd_head, i);
		print_redirections(current->red);
        current = current->next_cmd;
        i++;
    }
}

