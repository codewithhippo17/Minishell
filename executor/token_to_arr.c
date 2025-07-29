/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:19:14 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 06:05:18 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_structlen(t_token *token)
{
	int		i;
	t_token	*current;

	i = 0;
	current = token;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**token_to_arr(t_token *token)
{
	int		i;
	int		l;
	char	**cmd;
	t_token	*current;

	i = 0;
	current = token;
	l = ft_structlen(token);
	cmd = malloc((l + 1) * (sizeof(char *)));
	if (!cmd)
		return (NULL);
	while (current)
	{
		cmd[i] = ft_strdup(current->value);
		current = current->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	extract_args(t_minishell *minishell)
{
	t_script	*script;

	script = minishell->script;
	while (script)
	{
		script->cmd_args = token_to_arr(script->cmd_head);
		script = script->next_cmd;
	}
}
