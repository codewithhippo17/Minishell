/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:48:23 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/02 23:49:58 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-------------------**lexing**---------------------*/

#ifndef LEXER_H
# define LEXER_H

# include "./types.h"
t_token	*lexer(char *input);
void	append_token(t_token **head, t_token **tail, t_token *new_token);

t_token *parse_spaces(int *i, char *input);
t_token *parse_quoted(int *i, char *input, char quote);
t_token *parse_operator(int *i, char *input, char op);
t_token *parse_variable(int *i, char *input);
t_token *parse_word(int *i, char *input);

void	fill_token(t_token **token, char *value, t_flag flag, t_quote quote);

#endif
