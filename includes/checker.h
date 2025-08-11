/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:42:02 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:42:02 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "types.h"
# include <stdbool.h>

int		checker(t_token **token, t_minishell *minishell);
bool	is_word(t_token *token);
bool	is_op(t_token *token);
bool	check_quote(t_token *token);
char	*grabdel(t_token *token);
t_quote	grabquote(t_token *token);

#endif
