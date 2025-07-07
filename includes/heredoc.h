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

# define LEN_RANDOM 8

typedef struct s_heredoc
{
    int				fd;
    int             pid;
    int             status;
    char            *line;
    char			*filename;
    char            *del; // delimiter
    struct s_heredoc    *prev;
    struct s_heredoc	*next;
}	heredoc_t;

static heredoc_t *g_heredoc = NULL;


char    *ft_random(void);
heredoc_t	*init_heredoc(void);
void    free_heredoc(heredoc_t *hd);
void    free_heredoc_list(heredoc_t *hd);
void    add_heredoc(heredoc_t **head, heredoc_t *new);
#endif
