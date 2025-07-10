/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:24:28 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/03 00:24:29 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H

# include "types.h"
# include <stdbool.h>

bool    checker(t_token **token);
bool	is_word(t_token *token);
bool	is_op(t_token *token);
bool    check_quote(t_token *token);
char *grabdel(t_token *token);
t_quote grabquote(t_token *token);

#endif
