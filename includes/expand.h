/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:38:02 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/18 14:39:13 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "types.h"

void		ft_expander(t_token **token, t_minishell *minishell);
void		expander(char **string, t_minishell *minishell);
t_splited	*ft_spliter(char *word);

int			ft_len_split(char **split);
int			is_var_char(char c);
bool		last_space(char *str);
int			get_var_len(const char *str);
int			getnon_var_len(const char *str);
void		flag_join(t_token *c);
bool		no_var(char *value);
char		*char_to_str(char c);
t_token		*fill_var_token(char *varname);
t_splited	*init_inner(void);
void		flag_ambg(t_token *token);
int			is_var_start(char c);
char		*get_varname(char *str, int *i);
t_token		*fill_empty_splited(void);
void		insert_token(t_token **head, t_token *current, t_splited *splited);

#endif
