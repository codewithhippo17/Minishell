

#include "../minishell.h"

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
