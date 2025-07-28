/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 03:46:20 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 04:50:33 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stdlib.h>

void	append_script(t_script **head, t_script **tail, t_script *new_token)
{
	if (!new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		*tail = new_token;
	}
	else
	{
		(*tail)->next_cmd = new_token;
		*tail = new_token;
	}
}


/* t_cmd   *ft_syntax_tree() */

t_script *init_script(t_token *cmd, t_red *red, t_minishell *minishell)
{
    t_script *script;

    script = malloc(sizeof(t_script));
    script->red = red;
    script->cmd_head = cmd;
    script->next_cmd = NULL;
    return (script);
}

t_script *ft_parrsing(t_minishell *minishell)
{
    t_token     *tokens;
    t_token     *cmd;
    t_script    *script_head;
    t_script    *script_tail;
    t_red       *red;
    
    int i = 0;
    script_head = NULL;
    script_tail = NULL;
    tokens = lexer(minishell->input);
    checker(&tokens, minishell);
    //if (!checker(&tokens, minishell))
        // free and exit all
    ft_expander(&tokens, minishell);
    ft_join_tokens(&tokens);
    red = sub_red(tokens);
    cmd = grep_tokens(&tokens);
    while (cmd)
    {
        print_tokens(cmd, i);
        print_redirections(red);
        append_script(&script_head, &script_tail, init_script(cmd, red, minishell));
        red = sub_red(tokens);
        cmd = grep_tokens(&tokens);
        i++;
    }
    return (script_head);
}
