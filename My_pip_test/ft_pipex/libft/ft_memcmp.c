/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:10:16 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:10:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*s1t;
	unsigned char	*s2t;

	i = 0;
	s1t = (unsigned char *)s1;
	s2t = (unsigned char *)s2;
	if (!s1 && !s2 && !n)
		return (0);
	while (n--)
	{
		if (s1t[i] != s2t[i])
			return (s1t[i] - s2t[i]);
		i++;
	}
	return (0);
}
