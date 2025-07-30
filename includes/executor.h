/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 05:58:29 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/28 06:13:46 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "types.h"

void		extract_args(t_minishell *minishell);
int			calcule_cmd(t_script *script);
t_minishell	*shell(t_minishell *mini);
void		handle_command(t_minishell *minishell);
void		handle_pipe(t_minishell *mini);

#endif
