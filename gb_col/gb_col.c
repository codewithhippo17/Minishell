/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_col.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:58:43 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 19:00:13 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

static t_minishell	*g_minishell = NULL;
static t_collect	*g_head = NULL;
static t_collect	*g_tail = NULL;

void	collector_init_shell(t_minishell **shell, char **env)
{
	*shell = my_alloc(sizeof(t_minishell), SCOPE_SHELL);
	if (!(*shell))
	{
		perror("malloc:");
		exit(1);
	}
	set_env((*shell), env);
	(*shell)->status = 0;
	g_minishell = *shell;
}

void	collector_cleanup(t_mem_scope scope)
{
	t_collect	*prev;
	t_collect	*curr;
	t_collect	*next;

	prev = NULL;
	curr = g_head;
	while (curr)
	{
		next = curr->next;
		if (curr->scope == scope)
		{
			free(curr->ptr);
			if (curr == g_tail)
				g_tail = prev;
			delete_collected(&g_head, prev, &curr);
			curr = next;
		}
		else
		{
			prev = curr;
			curr = next;
		}
	}
}

void	cleanup_exit(int exit_code)
{
	t_collect	*curr;
	t_collect	*next;
	char		*input_backup;

	input_backup = NULL;
	if (g_minishell && g_minishell->input)
		input_backup = g_minishell->input;
	collector_cleanup(SCOPE_TEMP);
	collector_cleanup(SCOPE_SESSION);
	collector_cleanup(SCOPE_CHILD);
	collector_cleanup(SCOPE_SHELL);
	curr = g_head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	if (input_backup)
		free(input_backup);
	exit(exit_code);
}

void	collector_register(void *ptr, t_mem_scope scope)
{
	t_collect	*collect;

	collect = malloc(sizeof(t_collect));
	if (!collect)
		cleanup_exit(1);
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
