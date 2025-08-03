/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_col.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:58:43 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/02 04:40:01 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static t_minishell	*g_minishell = NULL;
static t_collect	*g_head = NULL;
static t_collect	*g_tail = NULL;

void	collector_init_shell(t_minishell *shell, char **env)
{
	shell = my_alloc(sizeof(t_minishell), SCOPE_SHELL);
	if (!shell)
	{
		perror("malloc:");
		exit(1);
	}
	set_env(shell, env);
	shell->status = 0;
	shell->input = NULL;
	g_minishell = shell;
	g_minishell->collect = g_head;
}

void	collector_cleanup(t_mem_scope scope)
{
	t_collect	*prev;
	t_collect	*curr;

	prev = NULL;
	curr = g_head;
	while (curr)
	{
		if (curr->scope == scope)
		{
			free(curr->ptr);
			delete_collected(&g_head, prev, &curr);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	cleanup_exit(int exit_code)
{
	collector_cleanup(0);
	collector_cleanup(1);
	collector_cleanup(2);
	collector_cleanup(3);
	free(g_minishell->input);
	exit(exit_code);
}

void	collector_register(void *ptr, t_mem_scope scope)
{
	t_collect	*collect;

	collect = malloc(sizeof(t_collect));
	if (!collect)
		return ;
	collect->ptr = ptr;
	collect->scope = scope;
	collect->next = NULL;
	append_collected(&g_head, &g_tail, collect);
}

void	*my_alloc(size_t size, t_mem_scope scope)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		cleanup_exit(1);
	collector_register(ptr, scope);
	return (ptr);
}
