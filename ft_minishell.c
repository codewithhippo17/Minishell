#include "minishell.h"

void free_split(char **s)
{
  int j = 0; 
  while (s[j])
  {
    free(s[j]);
    j++;
  }
  free(s);
}

void pwd(void)
{
  char cwd[PATH_MAX];
  char *s = getcwd(cwd, sizeof(cwd));
  if (s != NULL)
    printf("%s\n", cwd);
  else
  {
    free(s);
    ft_putstr_fd("getcwd(): Error\n", 2);
    return ;
  }
}

void cd(char *str)
{
  if (chdir(str) != 0)
  {
    ft_putstr_fd("chdir: Error", 2);
    return ;
  }
}

void echo(char *str)
{
  int i = 0;
  char **s = ft_split(str, ' '); //this need parce not split
  if (!s)
  {
    ft_putstr_fd("Error: Memory allocation failed\n", 2);
    return;
  }
  if (s[1] && ft_strncmp(s[1], "-n", ft_strlen("-n")) == 0)
    i = 1;
  while (s[++i])
  {
    printf("%s", s[i]);
    if (s[i + 1])
      printf("%c", ' ');
  }
  if (!s[1] || ft_strncmp(s[1], "-n", ft_strlen("-n")) != 0)
    printf("\n");
  free_split(s);
}

int	main(int argc, char *argv[])
{
	while (argc == 1 && argv)
	{
    char *str;
		str = readline("minishell$");
    add_history(str);
    //printf("%s\n", str);
    char **s = ft_split(str, ' ');
    if (!s)
    {
      free(str);
      return (EXIT_FAILURE);
    }
    if (s[0] && ft_strncmp(s[0], "echo", ft_strlen("echo")) == 0)
    {
      echo(str);
      free(str);
    }
    if (s[0] && ft_strncmp(s[0], "pwd", ft_strlen("pwd")) == 0)
    {
      pwd();
      free(str);
    }
    if (s[0] && ft_strncmp(s[0], "cd", ft_strlen("cd")) == 0)
    {
      cd(s[1]);
      free(str);
    }
    if (s[0] && ft_strncmp(s[0], "exit", ft_strlen("exit")) == 0)
    {
      free(str);
      free_split(s);
      return (EXIT_SUCCESS);
    }
    free_split(s);
	}
	return (EXIT_SUCCESS);
}
