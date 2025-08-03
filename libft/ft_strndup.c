/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:53:21 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/07/22 02:53:23 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s, int len, t_mem_scope scope)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)my_alloc((len + 1), scope);
	if (!tmp)
		return (NULL);
	while (s[i] && i < len)
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strndup("abcdef", 6));
}
*/
