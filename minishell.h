
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include </usr/include/readline/readline.h>
# include </usr/include/readline/history.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>


typedef enum e_arg{
  DQS,
  SQS,
  NQS
} t_arg;

typedef struct s_script{
  struct s_script *next;
  char *arg;
  t_arg type;
} t_script;

typedef struct s_minishell
{
	char	*input;
  char  **m_env;
	char	**cmd_args;
	int		status;
}			t_minishell;

//-------------------**ft_scarping**---------------------//
char **ft_parsing(t_script *script);

//-------------------**ft_scarping**-------------------//
t_script *ft_scarping(char *prompt);

//-------------------**build-in_cmd**-----------//
int	is_builtin(char **s);
void	execute_builtin(t_minishell *minishell);

//-------------------**external_cmd**-------------//
int	ft_exec_all(t_minishell *minishell);

//---------------ººfreesplitºº-----------------//
void		free_split(char **s);
void		ft_exit(char *error);

//----------------ººbuild-in_cmd_utilsºº------------------//
int			echo(char *str, int status);
int			cd(char *str, char **m_env);
int			pwd(void);
int		envierment(char **env);
int   ft_export(char **av, char **m_env);

//-----------------ººminishel_utils.cºº----------------//
char		*my_getenv(char *name, char **env);
char		*get_path(char *cmd, char **env);

#endif  
