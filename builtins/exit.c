/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:38:14 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/22 03:08:49 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_befor_exit(t_minishell *minishell)
{
	free(minishell->input);
	free_strings(minishell->script->cmd_args);
	free_strings(minishell->m_env);
	free_strings(minishell->s_env);
	free(minishell);
}

int	ft_my_exit(t_minishell *minishell)
{
	int		i;
	char	**str;

	str = minishell->script->cmd_args;
	if (minishell->script->cmd_args[1])
		i = ft_atoi(minishell->script->cmd_args[1]);
	printf("exit\n");
	if (str[1] && !str[2] && is_num(str[1]))
	{
		free_befor_exit(minishell);
		exit(i);
	}
	else if (str[1] && !is_num(str[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_befor_exit(minishell);
		exit(2);
	}
	else if (str[1] && str[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	else
	{
		free_befor_exit(minishell);
		exit(0);
	}
	return (0);
}
