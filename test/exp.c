#include "../minishell.h"
#include <stdio.h>
int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
    (void)argc;
    (void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
    
    char *str = ft_strdup("$HOME $PWD $HH@scdsdc");
    printf("%s\n", str);
    expander(&str, minishell->m_env);
    printf("%s\n", str);
	// printf("%s", my_getenv("PWDHOME12323", minishell->m_env));
    free(minishell);
	return (EXIT_SUCCESS);
}
