/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_col.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 01:58:43 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/01 04:38:27 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
#include <stddef.h>

static t_minishell *minishell = NULL;

void collector_init_shell(t_minishell *shell)
{
    minishell = shell;
}

void collectr_cleanup(t_mem_scope scope)
{
    // TODO: implement cleanup logic for all pointers in the given scope
}

void collector_register(void *ptr, t_mem_scope scope)
{
    // TODO: store the ptr in your collector (based on scope)
}

void *my_alloc(size_t size, t_mem_scope scope)
{
    void *ptr = malloc(size);
    if (!ptr)
        return NULL; // exit minishell
    collector_register(ptr, scope);
    return ptr;
}
