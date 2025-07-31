/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:02:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/22 03:03:38 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>
#include <string.h>

int	chlstdir(char **m_env)
{
	char	*lst_dir;

	lst_dir = my_getenv("OLDPWD", m_env);
	if (lst_dir != NULL)
		printf("%s\n", lst_dir);
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

int	update_old_pwd(char ***env, char *ft_var, char *var_value)
{
	int		i;
	char	**var;

	i = 0;
	while ((*env)[i])
	{
		var = ft_split((*env)[i], '=');
		if (ft_strcmp(var[0], ft_var) == 0)
		{
			if ((*env)[i] != NULL)
				free((*env)[i]);
			(*env)[i] = ft_strdup(var_value);
			if (!(*env)[i])
				return (1);
		}
		i++;
	}
	return (0);
}

int	cd(char **str, t_minishell *minishell)
{
	char	current_dir[PATH_MAX];
	char	*prev_dir;
	char	*pwd;

	if (str[1] && str[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd(): error"), 1);
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
	prev_dir = ft_strjoin("OLDPWD=", current_dir);
	update_old_pwd(&(minishell->m_env), "OLDPWD", prev_dir);
	update_old_pwd(&(minishell->s_env), "OLDPWD", prev_dir);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
		return (perror("getcwd(): error"), 1);
	pwd = ft_strjoin("PWD=", current_dir);
	update_old_pwd(&(minishell->m_env), "PWD", pwd);
	update_old_pwd(&(minishell->s_env), "PWD", pwd);
	return (free(prev_dir), free(pwd), prev_dir = NULL, pwd = NULL, 0);
}
