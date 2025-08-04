/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:48:10 by ybelghad          #+#    #+#             */
/*   Updated: 2024/11/03 01:50:12 by ybelghad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, t_mem_scope scope)
{
	char	*tmp;
	size_t	i;

	i = 0;
    if (!s)
    {
        return (NULL);
    }
    tmp = (char *)my_alloc(ft_strlen(s) + 1, scope);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
