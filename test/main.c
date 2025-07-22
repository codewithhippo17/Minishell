/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:11:49 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 05:45:00 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>
#include <stdio.h>

// This is the ONLY global variable allowed
int		g_signal_received = 0;

void	handle_main_signal(int sig)
{
	g_signal_received = sig; // Only store the signal number
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

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
        if (quote < 0 || quote > OBVIOUS)
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

void print_tokens(t_token *token)
{
    t_token *curr = token;

    printf("Lexer Output:\n    ");
    while (curr)
    {
        if (curr->type == PIPE)
        {
            printf("\n");
            curr = curr->next;
            continue ;
        }
        printf("[\e[1;34m{\"%s\"}\e[0m: \033[31m%s-%s\033[0m]", curr->value,  join_to_string(curr->join), ambg_to_string(curr->ambg));
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
        printf("  [\e[1;34m{\"path: %s\"}\e[0m: \033[31m%s-%s fd: %d\033[0m]", curr->path, flag_to_string(curr->type), ambg_to_string(curr->ambg), curr->fd);
        if (curr->next)
            printf("\033[32;1m🠒\033[0m");
        curr = curr->next;
    }
    printf("\n\n");
}


int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
	char		*input;
	t_token     *tokens;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
	signal(SIGINT, handle_main_signal);
	signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ in interactive mode
	while (argc == 1 && argv)
	{
		g_signal_received = 0; // Reset signal flag
		input = readline("minishell$> ");
		if (!input) // Ctrl+D
		{
			printf("exit\n");
			break ;
		}
		if (g_signal_received == SIGINT)
		{
			free(input);
			continue ; // Go to next prompt
		}
		if (*input)
		{
			add_history(input);
			tokens = lexer(input);
			checker(&tokens, minishell);
            /* tokens = ft_spliter(input); */
            ft_expander(&tokens, minishell);
            t_red *red = sub_red(tokens);
            print_tokens(tokens);
            print_redirections(red);
            
            /* printf("\033[31m$\033[0m%s\033[31m$\033[0m\n", input); */
            
		}
	}
	return (EXIT_SUCCESS);
}


