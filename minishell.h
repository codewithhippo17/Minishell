/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/09 19:21:07 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/ast.h"
# include "includes/bultins.h"
# include "includes/checker.h"
# include "includes/executor.h"
# include "includes/expand.h"
# include "includes/gbcol.h"
# include "includes/heredoc.h"
# include "includes/kill.h"
# include "includes/lexer.h"
# include "includes/pipex.h"
# include "includes/redirection.h"
# include "includes/signals.h"
# include "includes/types.h"
# include "libft/libft.h"
# include </usr/include/readline/history.h>
# include </usr/include/readline/readline.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/chardefs.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PIPE_ERROR1 "Syntax error: command cannot start with pipe '|'\n"
# define PIPE_ERROR2 "syntax error: command cannot end with a pipe '|'\n"
# define PIPE_ERROR3 "syntax error: command missing between pipes '|'\n"
# define RED_ERROR "syntax error: filepath or delimiter missing\n"
# define HEREDOC_ERROR "warning: heredoc canceled due to interruption\n"
# define UNCLOSED_QUOTES "Syntx error: Unclosed quotes\n"

//-------------------ººbuild-in_cmdºº-----------//

int		is_builtin(char **s);

//-------------------ººexternal_cmdºº-------------//
int		ft_exec_all(t_minishell *minishell);

//-----------------ººminishel_utilsºº----------------//
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);

//-------------ººminishell_helpreºº-------------------//
int		is_builtin(char **s);
int		is_piped(char *input);

//------------------ºº./minishell_set_envºº------------//
int		is_var(char *str);
char	**set_env_utils(char **env);
void	set_env(t_minishell *minishell, char **env);
void	print_script(t_script *script);
void	print_tokens(t_token *token, int nb);
void print_redirections(t_red *red);

// -----------------ººPIPEXºº------------------ //
int		pipex(int ac, t_minishell *mini);

//-----------------ººREVAMPºº-------------------/
// t_minishell	*shell(t_minishell *mini);
t_red	*sub_red(t_token *token);
void	ft_join_tokens(t_token **token);
// t_minishell	*shell(t_minishell *mini);
t_token	*token_init(void);
t_red	*red_init(void);
void	mini_update(t_minishell *mini, t_token *token);

#endif
