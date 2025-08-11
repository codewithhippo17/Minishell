/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 03:46:20 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 06:02:26 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_script	*init_script(t_token *cmd, t_red *red)
{
	t_script	*script;

	script = my_alloc(sizeof(t_script), SCOPE_SESSION);
	script->red = red;
	script->cmd_head = cmd;
	script->cmd_args = NULL;
	script->next_cmd = NULL;
	script->exit_status = -1;
	return (script);
}

t_script	*ft_parrsing(t_minishell *minishell)
{
	t_token		*tokens;
	t_token		*cmd;
	t_script	*script_head;
	t_script	*script_tail;
	t_red		*red;

	script_head = NULL;
	script_tail = NULL;
	tokens = lexer(minishell->input);
	if (checker(&tokens, minishell))
	{
		if (g_received_signal == SIGNAL_SIGINT)
			g_received_signal = SIGNAL_NONE;
		return (NULL);
	}
    // printf("lexer\n");
    // print_tokens(tokens, 1);
	ft_expander(&tokens, minishell);
    // printf("expander\n");
    // print_tokens(tokens, 2);
	ft_join_tokens(&tokens);
    // printf("join\n");
    // print_tokens(tokens, 3);
	red = sub_red(tokens);
    // printf("red\n");
    // print_redirections(red);
    // print_tokens(tokens, 4);
	cmd = grep_tokens(&tokens);
	while (cmd || red)
	{
		append_script(&script_head, &script_tail, init_script(cmd, red));
		red = sub_red(tokens);
		cmd = grep_tokens(&tokens);
	}
	if (!script_head || !script_tail)
		return (NULL);
	return (script_tail->next_cmd = NULL, script_head);
}
