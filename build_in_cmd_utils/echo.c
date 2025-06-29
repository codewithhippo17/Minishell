/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:04 by ybelghad          #+#    #+#             */
/*   Updated: 2025/06/12 18:03:04 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char *str, int status)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_split(str, ' '); // This will be a parsing job
	if (!s)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (1);
	}
	if (s[1] && ft_strncmp(s[1], "-n", ft_strlen("-n")) == 0)
		i = 1;
	if (s[1] && ft_strncmp(s[1], "$?", ft_strlen("$?")) == 0)
		printf("%d", status);
	else
	{
		while (s[++i])
		{
			printf("%s", s[i]);
			if (s[i + 1])
				printf("%c", ' ');
		}
	}
	if (!s[1] || ft_strncmp(s[1], "-n", ft_strlen("-n")) != 0)
		printf("\n");
	free_split(s);
	return (0);
}
