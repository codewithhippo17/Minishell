/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:58:26 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/03 00:01:12 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

#include <stddef.h>

/*------------------------------------**the full logic and data structure of the parsser**--------------------------------------*/

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
    ES,           // $? special variable (handled like VAR but tagged separately)
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

typedef struct s_token
{
    char            *value;       // The string (e.g. echo, >>, file.txt)
    t_flag          type;         // CMD, ARG, PIPE, RR, etc.
    t_quote         quote;        // Quote context: affects expansion
    heredoc_t       *hd;          // Pointer to heredoc data 
    struct s_token  *next;        // Next token in list
    struct s_token  *prev;
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

#endif
