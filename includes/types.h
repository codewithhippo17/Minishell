/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:58:26 by ehamza            #+#    #+#             */
/*   Updated: 2025/08/01 04:47:09 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

# define SIGNAL_NONE 0
# define SIGNAL_SIGINT 1
# define SIGNAL_SIGQUIT 2


typedef enum e_free
{
	FREE,
	STILL,
}						t_free;

typedef enum e_scope
{
	SCOPE_TEMP,
	SCOPE_SESSION,
	SCOPE_CHILD,
	SCOPE_SHELL,
}						t_mem_scope;

typedef enum e_builtin_name
{
	ECHO,
	CD,
	PWD,
	ENV,
	EXPORT,
	UNSET,
	EXIT,
	UNKNOWN
}						t_builtin_name;

typedef enum e_join
{
	J,
	JL,
	JR,
	NJ,
	NONE
}						t_join;

typedef enum e_quote
{
	NQS,
	SQS,
	DQS,
	UQS
}						t_quote;

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
	ERROR
}						t_flag;

typedef enum e_ambg
{
	AMBG,
	OBV,
}						t_ambg;

typedef struct s_heredoc
{
	int					fd;
	int					tmp_fd;
	int					pid;
	int					status;
	char				*line;
	char				*filename;
	char				*del;
	t_quote				quote;
	t_ambg				ambg;
}						t_heredoc;

typedef struct s_red
{
	int					fd;
	int					saved_stdin;
	int					saved_stdout;
	char				*path;
	t_flag				type;
	t_ambg				ambg;
	struct s_red		*next;
}						t_red;

typedef struct s_token
{
	char				*value;
	t_flag				type;
	t_quote				quote;
	t_join				join;
	t_ambg				ambg;
	t_heredoc			*hd;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_splited
{
	t_token				*head;
	t_token				*tail;
	char				**split;
	int					len;
}						t_splited;

typedef struct s_script
{
	t_token			*cmd_head;
	t_red			*red;
	char			**cmd_args;
	int				saved_stdin;
	int				saved_stdout;
	int				exit_status;
	struct s_script	*next_cmd;
}					t_script;

typedef struct s_collect
{
	void				*ptr;
	t_mem_scope			scope;
	struct s_collect	*next;
}						t_collect;

typedef struct s_minishell
{
	char				*input;
	char				**m_env;
	char				**s_env;
	int					status;
	t_script			*script;
    t_collect           *collect;
}						t_minishell;

#endif
