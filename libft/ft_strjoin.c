/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:32:20 by ybelghad          #+#    #+#             */
/*   Updated: 2025/08/09 19:06:20 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_mem_scope scope)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = (char *)my_alloc((ft_strlen(s1) + ft_strlen(s2) + 1), scope);
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			res[j++] = s2[i++];
	}
	res[j] = '\0';
	return (res);
}
