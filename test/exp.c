#include "../minishell.h"
int	main(int argc, char *argv[], char **env)
{
	t_minishell	*minishell;
    (void)argc;
    (void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->status = 0;
	if (set_env(minishell, env))
		free_exit_minishell(minishell, EXIT_FAILURE);
    
    char *str = ft_strdup("$HOME $PWD $HHH $45dsdsd dscscsdc sdvvdsvv$ scsdc");
    printf("%s\n", str);
    expander(&str, minishell->m_env);
    printf("%s\n", str);
	free(minishell);
	return (EXIT_SUCCESS);
}
