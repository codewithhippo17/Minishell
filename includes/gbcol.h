/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gbcol.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 04:39:10 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/01 04:42:04 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBCOL_H
# define GBCOL_H

#include "../includes/types.h"

void collector_init_shell(t_minishell *shell);
void collectr_cleanup(t_mem_scope scope);
void collector_register(void *ptr, t_mem_scope scope);
void *my_alloc(size_t size, t_mem_scope scope);

#endif
