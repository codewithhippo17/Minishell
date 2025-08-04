/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:04 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/22 03:11:54 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chek_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-')
		i++;
	else
		return (0);
	while (flag[i])
	{
		if (flag[i] == 'n')
			i++;
		else
			return (0);
	}
	return (1);
}

int	echo(char **s)
{
	int	i;

	i = 1;
	if (!s[i])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	while (s[i] && chek_flag(s[i]))
		i++;
	while (s[i])
	{
		ft_putstr_fd(s[i], 1);
		if (s[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!chek_flag(s[1]))
		ft_putchar_fd('\n', 1);
	return (0);
}
