/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:03:04 by ybelghad          #+#    #+#             */
/*   Updated: 2025/07/06 19:17:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int chek_flag(char *flag)
{
  int i;
  i = 0;
  if(flag[i] == '-')
    i++;
  else
    return (0);
  while(flag[i])
  {
    if(flag[i] == 'n')
      i++;
    else
     return (0);
  }
  return (1);
}

int	echo(char *str, int status)
{
	int		i;
	char	**s;

	i = 1;
	s = ft_split(str, ' '); // This will be a parsing job
	if (!s)
	{
		ft_putstr_fd("Error: Memory allocation failed\n", 2);
		return (1);
	}
	while (s[i] && chek_flag(s[i]))
		i++;
	if (s[i] && ft_strncmp(s[i], "$?", ft_strlen("$?")) == 0)
		printf("%d", status);
	else
	{
		while (s[i])
		{
			printf("%s", s[i]);
			if (s[i + 1])
				printf("%c", ' ');
      i++;
		}
	}
	if (!chek_flag(s[1]))
		printf("\n");
	free_strings(s);
	return (0);
}
