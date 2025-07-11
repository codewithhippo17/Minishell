/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:10:25 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:10:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_tokens(char const *s, char c)
{
	size_t	tokens;

	tokens = 0;
	while (*s)
	{
		while ((*s == c) && *s)
			s++;
		if (*s != '\0')
		{
			tokens++;
			while ((*s != c) && *s)
				s++;
		}
	}
	return (tokens);
}

static int	safe_malloc(char **ns, int i, size_t l_token)
{
	ns[i] = malloc((l_token + 1) * sizeof(char));
	if (!ns[i])
	{
		while (i > 0)
			free(ns[--i]);
		free(ns);
		return (1);
	}
	return (0);
}

static int	fill_ns(char **ns, char const *s, char c)
{
	int		i;
	size_t	l_token;

	i = 0;
	while (*s)
	{
		l_token = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			l_token++;
			s++;
		}
		if (l_token)
		{
			if (safe_malloc(ns, i, l_token))
				return (1);
			ft_strlcpy(ns[i], s - l_token, l_token + 1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**ns;

	if (!s)
		return (NULL);
	tokens = count_tokens(s, c);
	ns = malloc((tokens + 1) * sizeof(char *));
	if (!ns)
		return (NULL);
	ns[tokens] = NULL;
	if (fill_ns(ns, s, c))
		return (NULL);
	return (ns);
}
