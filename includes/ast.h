/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 03:41:48 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/27 05:09:43 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "types.h"

void		delete_token(t_token **head, t_token **token);
t_token		*grep_tokens(t_token **tokens);
t_script	*ft_parrsing(t_minishell *minishell);

#endif
