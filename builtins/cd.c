/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:02:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/11 23:53:09 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chlstdir(char **m_env)
{
	char	*lst_dir;

	lst_dir = my_getenv("OLDPWD", m_env);
	if (lst_dir != NULL)
	{
		ft_putstr_fd(lst_dir, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		ft_putstr_fd("No previous directory\n", 2);
		return (1);
	}
	if (chdir(lst_dir) != 0)
	{
		perror("cd error");
		return (1);
	}
	return (0);
}

int	chthmdir(char **m_env)
{
	char	*home;

	home = my_getenv("HOME", m_env);
	if (home == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	else if (chdir(home) != 0)
	{
		perror("cd error");
		return (1);
	}
	return (0);
}

int	update_old_pwd(char ***env, char *new_var, char *var_value)
{
	int		i;
	char	**var;

	i = 0;
	while ((*env)[i])
	{
		var = ft_split((*env)[i], '=', SCOPE_TEMP);
		if (ft_strcmp(var[0], new_var) == 0)
			(*env)[i] = ft_strdup(var_value, SCOPE_SHELL);
		i++;
	}
	return (0);
}

int	update_env(t_minishell *minishell)
{
	char	*pwd;
	char	*prev_dir;
	char	current_dir[PATH_MAX];

	prev_dir = ft_strjoin("OLDPWD=", my_getenv("PWD", minishell->m_env),
			SCOPE_TEMP);
	if (!prev_dir)
		return (1);
	update_old_pwd(&(minishell->m_env), "OLDPWD", prev_dir);
	update_old_pwd(&(minishell->s_env), "OLDPWD", prev_dir);
	if (!getcwd(current_dir, sizeof(current_dir)))
		return (perror("getcwd"), 1);
	pwd = ft_strjoin("PWD=", current_dir, SCOPE_TEMP);
	update_old_pwd(&(minishell->m_env), "PWD", pwd);
	update_old_pwd(&(minishell->s_env), "PWD", pwd);
	return (0);
}

int	cd(char **str, t_minishell *minishell)
{
	if (str[1] && str[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (str[1] == NULL || str[1][0] == '\0' || ft_strncmp(str[1], "~",
			ft_strlen("~")) == 0)
	{
		if (chthmdir(minishell->m_env))
			return (1);
	}
	else if (ft_strncmp(str[1], "-", ft_strlen("-")) == 0)
	{
		if (chlstdir(minishell->m_env))
			return (1);
	}
	else if (chdir(str[1]) != 0)
		return (perror("cd error"), 1);
	if (update_env(minishell))
		return (1);
	return (0);
}
