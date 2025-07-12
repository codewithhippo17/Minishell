/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 23:25:21 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/06 23:25:53 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "types.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>

# define LEN_RANDOM 8

char    *ft_random(void);
heredoc_t	*init_heredoc(void);
void    free_heredoc(heredoc_t *hd);
void    free_heredoc_list(heredoc_t *hd);
void    add_heredoc(heredoc_t **head, heredoc_t *new_hd);
int heredoc(heredoc_t *hd, t_minishell *minishell);
void ft_heredoc(t_token *token, char *delimiter, t_quote quote, t_minishell *minishell);
void	write_file_to_stdout(int fd);
#endif
