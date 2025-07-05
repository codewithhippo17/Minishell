/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:24:01 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/03 00:24:02 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


bool    checker(t_token *token)
{
    if (check_quote(token) == false)
        return (false);
    t_token *current;

    current = token;
    while (current)
    {
        if (current->type == PIPE)
        {
            if (!current->prev || (current->prev->type == WS && !current->prev->prev))
                return (false);
            if (!current->next || (current->next->type == WS && !current->next->next))
                return (false);
            if (current->next->type == PIPE || (current->next->type == WS && current->next->next->type == PIPE))
                return (false);
        }
        if (is_op(current) == true)
        {
            if (is_word(current->next) == false)
                return (false);
        }
        current= current->next;
    }
    return (true);
}


int	main(int argc, char *argv[], char **env)
{
    char *input;
	while (argc == 1 && argv)
	{
		input = readline("minishell$");
        t_token *tokens = lexer(input);
        if (checker(tokens) == false)
        {
            printf("\nNNNNNNNNN\n");
        }
        else {
        printf("\nYYYYYYYYYY\n");
        }
    }

	return (EXIT_SUCCESS);
}
