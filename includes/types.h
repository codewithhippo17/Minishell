/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:58:26 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/15 11:03:48 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

typedef enum e_join
{
    J,
    JL,
    JR,
    NJ,
    NONE
}   t_join;


typedef enum e_quote
{
	NQS,
	SQS,
	DQS,
	UQS
}					t_quote;

typedef enum e_flag
{
	WORD,
	CMD,
	ARG,
	WS,
	PIPE,
	LR,
	RR,
	DLR,
	DRR,
	HEREDOC,
	VAR,
	ES,
	ERROR
}					t_flag;



typedef struct s_cmd
{
	char			*arg;
	t_flag			arg_type;
	t_quote			word_type;
	struct s_cmd	*next_cmd;
	struct s_cmd	*next_arg;
}					t_cmd;

typedef struct s_heredoc
{
	int				fd;
	int				tmp_fd;
	int				pid;
	int				status;
	char			*line;
	char			*filename;
	char			*del;
	t_quote			quote;
}					t_heredoc;

typedef struct s_token
{
	char			*value;
	t_flag			type;
	t_quote			quote;
    t_join          join;
	t_heredoc		*hd;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_splited
{
	t_token	*head;
	t_token	*tail;
	char	**split;
	int		len;
} t_splited;

typedef struct s_minishell
{
	char			*input;
	char			**m_env;
	char			**s_env;
	char			**cmd_args;
	int				status;
}					t_minishell;

#endif
