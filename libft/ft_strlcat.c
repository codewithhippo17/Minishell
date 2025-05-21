/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:39:38 by ybelghad          #+#    #+#             */
/*   Updated: 2024/11/01 17:39:09 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dl;
	size_t	sl;
	size_t	mxc;

	i = 0;
	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	mxc = (size - dl - 1);
	if (size == 0)
		return (sl);
	if (size <= dl)
		return (sl + size);
	while (i < mxc && src[i])
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[dl + i] = '\0';
	return (dl + sl);
}
