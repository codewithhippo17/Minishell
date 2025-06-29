/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:09:46 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:09:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	actual_len;
	char	*st;

	if (!s)
		return (NULL);
	actual_len = ft_strlen(s);
	if (start >= actual_len)
		return (ft_calloc(1, sizeof(char)));
	if (start + len > actual_len)
		len = actual_len - start;
	st = ft_calloc(len + 1, sizeof(char));
	if (!st)
		return (NULL);
	ft_strlcpy(st, s + start, len + 1);
	return (st);
}
