/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/28 06:00:23 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/ast.h"
# include "includes/bultins.h"
# include "includes/checker.h"
# include "includes/expand.h"
# include "includes/heredoc.h"
# include "includes/kill.h"
# include "includes/lexer.h"
# include "includes/pipex.h"
# include "includes/redirection.h"
# include "includes/executor.h"
# include "libft/libft.h"
# include </usr/include/readline/history.h>
# include </usr/include/readline/readline.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/chardefs.h>
# include <stddef.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//-------------------ººbuild-in_cmdºº-----------//

int		is_builtin(char **s);
void	execute_builtin(t_minishell *minishell, t_script *script);

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
int		set_env(t_minishell *minishell, char **env);
void	print_tokens(t_token *token, int i);
void	print_redirections(t_red *red);

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
