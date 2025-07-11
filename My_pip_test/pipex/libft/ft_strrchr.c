/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:09:26 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	sl;
	int	i;

	sl = ft_strlen(str);
	i = sl;
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)&str[i++]);
		i--;
	}
	return (0);
}
