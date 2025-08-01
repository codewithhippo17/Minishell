

#include "../minishell.h"

t_builtin_name which_bultin(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return ECHO;
	if (ft_strcmp(cmd, "cd") == 0)
		return CD;
	if (ft_strcmp(cmd, "pwd") == 0)
		return PWD;
	if (ft_strcmp(cmd, "env") == 0)
		return ENV;
	if (ft_strcmp(cmd, "export") == 0)
		return EXPORT;
	if (ft_strcmp(cmd, "unset") == 0)
		return UNSET;
	if (ft_strcmp(cmd, "exit") == 0)
		return EXIT;
	return UNKNOWN;
}

typedef int (*t_builtin_fn)(t_minishell *, t_script *);

static t_builtin_fn g_builtin_dispatch[] = {
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_env,
	builtin_export,
	builtin_unset,
	builtin_exit,
	builtin_unknown
};


int	execute_builtin(t_minishell *minishell, t_script *script, t_builtin_name name)
{
    minishell->status = g_builtin_dispatch[name](minishell, script);
    return (minishell->status);
}
