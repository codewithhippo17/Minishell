/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:38:14 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/09 18:54:26 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

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

size_t	ft_atol(const char *str)
{
	size_t	i;
	size_t	n;
	size_t	s;

	i = 0;
	n = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		s *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (s * n);
}

int	ft_my_exit(t_script *script)
{
	size_t	i;
	char	**str;

	i = 0;
	str = script->cmd_args;
	if (str[1])
		i = ft_atol(script->cmd_args[1]);
	printf("exit\n");
	if (str[1] && (!is_num(str[1]) || (i > LONG_MAX)))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		cleanup_exit(2);
	}
	else if (str[1] && str[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	else if (str[1] && !str[2] && is_num(str[1]))
		cleanup_exit(i);
	else
		cleanup_exit(0);
	return (0);
}
