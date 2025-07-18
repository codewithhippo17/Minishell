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

void	expander(char **string, char **env);
t_splited	*ft_spliter(char *word);
int	ft_len_split(char **split);
int	is_var_char(char c);
bool	last_space(char *str);
int	get_var_len(const char *str);
int	getnon_var_len(const char *str);
#endif
