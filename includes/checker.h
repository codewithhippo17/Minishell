/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:24:28 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/22 03:13:52 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "types.h"
# include <stdbool.h>

int	checker(t_token **token, t_minishell *minishell);
bool	is_word(t_token *token);
bool	is_op(t_token *token);
bool	check_quote(t_token *token);
char	*grabdel(t_token *token);
t_quote	grabquote(t_token *token);

#endif
