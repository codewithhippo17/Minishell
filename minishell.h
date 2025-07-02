/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/02 18:13:17 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/chardefs.h>
# include <stdio.h>
# include </usr/include/readline/history.h>
# include </usr/include/readline/readline.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//------------------------------------**the full logic and data structure of the parsser**--------------------------------------//

/*
    Pipeline overview:
    ------------------------------------------------------------------------------
    char *input = readline("> ");               // Step 0: Get input
    t_token *tokens = lexer(input);             // Step 1: Tokenize into words, operators
    t_token *expanded = expand(tokens, env);    // Step 2: Expand variables
    t_cmd   *cmd_tree = parser(expanded);       // Step 3: Parse tokens into t_cmd structure
    executor(cmd_tree);                         // Step 4: Execute parsed command tree
    ------------------------------------------------------------------------------
*/

//------------- ENUMS --------------//

typedef enum e_quote
{
    NQS, // No quotes (unquoted)
    SQS, // Single quotes ('...')
    DQS, // Double quotes ("...")
    UQS  // Unclosed quoted sequence ("... , '...)
} t_quote;

typedef enum e_flag {
    WORD,         // Word
    CMD,          // Command (first word of a command segment)
    ARG,          // Any argument (e.g., -l, "file", etc.)
    WS,           // White spaces (e.g., ' ', '\t')
    PIPE,         // |
    LR,           // <
    RR,           // >
    DLR,          // <<
    DRR,          // >>
    VAR,          // $VAR
    ASSIGN,       // VAR=VALUE
    ES,   // $? special variable (handled like VAR but tagged separately)
    ERROR
} t_flag;

//------- PARSED COMMAND NODE -------//

typedef struct s_cmd 
{
    char            *arg;         // String value (e.g. "ls", "file.txt", "hello")
    t_flag          arg_type;     // CMD, ARG, PIPE, RR, etc.
    t_quote    word_type;    // Was this word quoted? (affects expansion)
    struct s_cmd    *next_cmd;    // Next command in sequence (pipe or redirection)
    struct s_cmd    *next_arg;    // Next argument in current command
} t_cmd;

//------- EXAMPLE TREE STRUCTURE ------//

/*
Parsed structure for: cat < infile.txt | grep "hello" > outfile.txt

t_cmd: "cat"     (CMD)
 └── next_arg   → NULL
 └── next_cmd   →
      " < "     (LR)
        └── next_arg → "infile.txt" (ARG)
        └── next_cmd →
             "|"     (PIPE)
              └── next_cmd →
                   "grep" (CMD)
                    └── next_arg → "hello" (ARG, DQS)
                    └── next_cmd →
                         ">" (RR)
                          └── next_arg → "outfile.txt" (ARG)

 Alternative visual representation:

cat (CMD)
 └── < (LR)
      └── infile.txt (ARG)
           └── | (PIPE)
                └── grep (CMD)
                     └── "hello" (ARG)
                          └── > (RR)
                               └── outfile.txt (ARG)
*/

//------------------------------------**the full logic and data structure of the lexer**------------------------------------------//

/*
    Lexer Pipeline Overview:
    ------------------------------------------------------------------------------
    char *input = readline("> ");        // Step 0: Get input from user
    t_token *tokens = lexer(input);      // Step 1: Tokenize input into linked list
    ------------------------------------------------------------------------------
*/


//------------------------------ TOKEN STRUCTURE ----------------------------------------//

typedef struct s_token
{
    char            *value;       // The string (e.g. echo, >>, file.txt)
    t_flag          type;         // CMD, ARG, PIPE, RR, etc.
    t_quote         quote;        // Quote context: affects expansion
    struct s_token  *next;        // Next token in list
}   t_token;

//-------------------------- EXAMPLE TOKEN LIST (ASCII) ---------------------------------//

/*
Input:
    echo "hello $USER" > out.txt | grep txt | cat << EOF

Lexer Output:
    [echo] ──▶ ["hello $USER"] ──▶ [>] ──▶ [out.txt] ──▶ [|] ──▶ [grep] ──▶ [txt] ──▶ [|] ──▶ [cat] ──▶ [<<] ──▶ [EOF]

Summary:
    [echo]          → CMD       | NO_QUOTE
    ["hello $USER"] → ARG       | DOUBLE_QUOTE
    [>]             → RR        | NO_QUOTE
    [out.txt]       → ARG       | NO_QUOTE
    [|]             → PIPE      | NO_QUOTE
    [grep]          → CMD       | NO_QUOTE
    [txt]           → ARG       | NO_QUOTE
    [|]             → PIPE      | NO_QUOTE
    [cat]           → CMD       | NO_QUOTE
    [<<]            → DLR       | NO_QUOTE
    [EOF]           → ARG       | NO_QUOTE
*/

typedef struct s_script
{
    t_cmd **cmd;
} t_script;

typedef struct s_var
{
  char *var;
  char *value;
  struct s_var *next_var;
} t_var;

typedef struct s_minishell
{
	char	*input;
	char	**m_env;
	char	**s_env;
	char	**cmd_args;
	int		status;
}			t_minishell;

//-------------------**lexing**---------------------//

void	append_token(t_token **head, t_token **tail, t_token *new_token);

t_token *parse_spaces(int *i, char *input);
t_token *parse_quoted(int *i, char *input, char quote);
t_token *parse_operator(int *i, char *input, char op);
t_token *parse_variable(int *i, char *input);
t_token *parse_word(int *i, char *input);

void	fill_token(t_token **token, char *value, t_flag flag, t_quote quote);

//-------------------**build-in_cmd**-----------//

int			is_builtin(char **s);
void		execute_builtin(t_minishell *minishell);

//-------------------**external_cmd**-------------//

int			ft_exec_all(t_minishell *minishell);

//---------------ººfreesplitºº-----------------//

void		free_split(char **s);
void		ft_exit(char *error);

//----------------ººbuild-in_cmd_utilsºº------------------//

int			echo(char *str, int status);
int			cd(char *str, t_minishell *minishell);
int			pwd(void);
int			envierment(char **m_env);

// int					ft_export(char **av, char **m_env);

int	update_variable(char *s, char **env, int i);
int			exports(char *var, char ***env);
int			exec_export(t_minishell *minishell);
int	unset_env(char *var, char ***env);
int	exec_unset(t_minishell *minishell);

//-----------------ººminishel_utils.cºº----------------//

char		*my_getenv(char *name, char **env);
char		*get_path(char *cmd, char **env);

// --------------ººPIPEX_UTILSºº--------------- //

void		ft_free_tab(char **tab);
void		ft_exit_status(char *error, int status);
void		ft_free_exit(char **args, char *erno, int status);
void		ft_close_wait_exit(int p_fd[], int pid1, int pid2);

// -----------------ººPIPEXºº------------------ //
void		pipex(t_minishell *minishell);

#endif
