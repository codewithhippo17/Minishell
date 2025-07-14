/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:21:03 by ybelghad          #+#    #+#             */
/*   Updated: 2024/11/04 10:02:48 by ybelghad         ###   ########.fr       */
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


/* #include <stdio.h>

int main()
{
    char *s = ft_substr("", 5, 0);
    printf("AAA%sAAA", s);
    free(s);
} */
