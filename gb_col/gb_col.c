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
#include <stdlib.h>

static t_minishell *minishell = NULL;
static t_collect *head = NULL;
static t_collect *tail = NULL;

void collector_init_shell(t_minishell *shell)
{
    minishell = shell;
    minishell->collect = head;
}

// CODE: implement cleanup logic for all pointers in the given scope

void collectr_cleanup(t_mem_scope scope)
{
    t_collect *prev;
    t_collect *curr;

    prev = NULL;
    curr = head;
    while (curr)
    {
        if (curr->scope == scope)
        {
            free(curr->ptr);
            delete_collected(&head, prev, &curr);
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

// TODO: store the ptr in your collector (based on scope)


void collector_register(void *ptr, t_mem_scope scope)
{
    t_collect *collect;


    collect = malloc(sizeof(t_collect));
    if (!collect)
        return; // exit shell
    collect->ptr = ptr;
    collect->scope = scope;
    collect->next = NULL;
    append_collected(&head, &tail, collect);
}

void *my_alloc(size_t size, t_mem_scope scope)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL; // exit minishell
    collector_register(ptr, scope);
    return ptr;
}
