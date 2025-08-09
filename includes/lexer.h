/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:43:07 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:43:07 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*-------------------**lexing**---------------------*/

#ifndef LEXER_H
# define LEXER_H

# include "./types.h"

t_token	*lexer(char *input);
void	append_token(t_token **head, t_token **tail, t_token *new_token);
t_token	*parse_spaces(int *i, char *input);
t_token	*parse_quoted(int *i, char *input, char quote);
t_token	*parse_operator(int *i, char *input, char op);
t_token	*parse_variable(int *i, char *input);
t_token	*parse_word(int *i, char *input);

void	fill_token(t_token **token, char *value, t_flag flag, t_quote quote);

#endif
