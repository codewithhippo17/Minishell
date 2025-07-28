/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:19:14 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/22 11:19:14 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_init(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup("cat");
	token->next = NULL;
	return (token);
}

t_red	*red_init(void)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	red->fd = -1;
	red->path = ft_strdup("minishell.c");
	red->next = NULL;
	return (red);
}

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

void	mini_update(t_minishell *mini, t_token *token)
{
	t_minishell	*current;
	t_token		*head;

	current = mini;
	head = token;
	while (current)
	{
		current->cmd_args = token_to_arr(head);
        current->red = head;
		current = current->next;
		head = head->next;
	}
}
