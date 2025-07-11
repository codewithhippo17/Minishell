/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:15:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/06 19:21:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
//-----------------------//
# include "libft/libft.h"
# include </usr/include/readline/history.h>
# include </usr/include/readline/readline.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <linux/limits.h>
# include <readline/chardefs.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_minishell
{
	char	*input;
	char	**m_env;
	char	**s_env;
	char	**cmd_args;
	int		status;
}			t_minishell;

//-------------------ººbuild-in_cmdºº-----------//
int			is_builtin(char **s);
void		execute_builtin(t_minishell *minishell);

//----------------ººbuild-in_cmd_utilsºº------------------//
int			echo(char *str, int status);
int			cd(char *str, t_minishell *minishell);
int			pwd(void);
int			envierment(char **m_env);
int			ft_my_exit(t_minishell *minishell);
int			update_variable(char *s, char **env, int i);
int			exports(char *var, char ***env);
int			exec_export(t_minishell *minishell);
int			unset_env(char *var, char ***env);
int			exec_unset(t_minishell *minishell);

//-------------------ººexternal_cmdºº-------------//
int			ft_exec_all(t_minishell *minishell);

//---------------ººfree_exitºº-----------------//
void		free_strings(char **s);
void		ft_exit(char *error);
void		free_exit_minishell(t_minishell *minishell, int status);

//-----------------ººminishel_utilsºº----------------//
char		*my_getenv(char *name, char **env);
char		*get_path(char *cmd, char **env);

//-------------ººminishell_helpreºº-------------------//
int			is_builtin(char **s);
int			is_piped(char *input);

//------------------ºº./minishell_set_envºº------------//
char		**set_env_utils(char **env);
int			set_env(t_minishell *minishell, char **env);

// -----------------ººPIPEXºº------------------ //

#endif
