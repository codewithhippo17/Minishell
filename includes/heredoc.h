/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:25:21 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/15 11:04:38 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../libft/libft.h"
# include "types.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

# define LEN_RANDOM 8

char		*ft_random(void);
t_heredoc	*init_heredoc(void);
void		free_heredoc(t_heredoc *hd);
void		free_heredoc_list(t_heredoc *hd);
void		add_heredoc(t_heredoc **head, t_heredoc *new_hd);
int			heredoc(t_heredoc *hd, t_minishell *minishell);
int         ft_heredoc(t_token *token, char *delimiter, t_quote quote,
				t_minishell *minishell);

#endif
