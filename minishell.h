
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>


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

t_script *ft_scarping(char *prompt);

#endif  