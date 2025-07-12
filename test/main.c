#include "../minishell.h"
#include <signal.h>

// This is the ONLY global variable allowed
int g_signal_received = 0;

void handle_main_signal(int sig)
{
    g_signal_received = sig;  // Only store the signal number
    if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}


void ft_free(t_token *token)
{
    t_token *tmp;
    while (token)
    {
        tmp = token;
        token = token->next;
        free(tmp->value);
        free(tmp);
    }
}



int	main(int argc, char *argv[], char **env)
{
    t_minishell	*minishell;
    (void)argc;
    (void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
    char *input;
    
    // Set up signal handling for main shell
    signal(SIGINT, handle_main_signal);
    signal(SIGQUIT, SIG_IGN);  // Ignore Ctrl+\ in interactive mode
    
    while (argc == 1 && argv)
    {
        g_signal_received = 0;  // Reset signal flag
        
        input = readline("minishell$> ");
        if (!input)  // Ctrl+D
        {
            printf("exit\n");
            break;
        }
        
        // Check if signal was received during readline
        if (g_signal_received == SIGINT)
        {
            free(input);
            continue;  // Go to next prompt
        }
        
        if (*input)
        {
            add_history(input);
            
            t_token *tokens = lexer(input);

            
            if (checker(&tokens, minishell) == false)
            {
                printf("\nNNNNNNNNN\n");
            }
            else 
            {
                printf("\nYYYYYYYYYY\n");
                // Execute commands here
            }
            
            ft_free(tokens);
        }
        
        free(input);
    }
    
    return (EXIT_SUCCESS);
}

/*
* void	print_tokens(t_token *token)
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
*/
