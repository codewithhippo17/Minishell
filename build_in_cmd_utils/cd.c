/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:02:39 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:02:39 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	cd(char *str, t_minishell *minishell)
{
	char	current_dir[PATH_MAX];
	char	*prev_dir;

	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		perror("getcwd(): error");
		return (1);
	}
	if (str == NULL || *str == '\0' || ft_strncmp(str, "~",
			ft_strlen("~")) == 0)
	{
		if (chthmdir(minishell->m_env))
			return (1);
	}
	else if (ft_strncmp(str, "-", ft_strlen("-")) == 0)
	{
		if (chlstdir(minishell->m_env))
			return (1);
	}
	else if (chdir(str) != 0)
	{
		perror("cd error");
		return (1);
	}
	prev_dir = ft_strjoin("OLDPWD=", current_dir);
	exports(prev_dir, &(minishell->m_env));
	exports(prev_dir, &(minishell->s_env));
	free(prev_dir);
	prev_dir = NULL;
	return (0);
}
