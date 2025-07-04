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
# include "includes/lexer.h"
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

typedef struct s_minishell
{
	char	*input;
	char	**m_env;
	char	**s_env;
	char	**cmd_args;
	int		status;
}			t_minishell;

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
