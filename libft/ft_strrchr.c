/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:11:56 by ybelghad          #+#    #+#             */
/*   Updated: 2024/11/03 02:29:02 by ybelghad         ###   ########.fr       */
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
