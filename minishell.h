#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include </usr/include/readline/readline.h>
# include </usr/include/readline/history.h>

void	ft_putchar_fd(char c, int fd);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif // !MINISHELL_H
