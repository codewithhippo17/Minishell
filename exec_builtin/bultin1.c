#include "../minishell.h"

int	builtin_echo(t_minishell *m, t_script *s)
{
	return (echo(s->cmd_args));
}

int	builtin_cd(t_minishell *m, t_script *s)
{
	return (cd(s->cmd_args, m));
}

int	builtin_pwd(t_minishell *m, t_script *s)
{
	return (pwd());
}

int	builtin_env(t_minishell *m, t_script *s)
{
	return (envierment(m->m_env));
}
