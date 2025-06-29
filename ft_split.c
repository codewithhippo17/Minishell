/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:30:27 by ehamza            #+#    #+#             */
/*   Updated: 2024/11/02 15:12:57 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little || little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)big + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

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

static int	ft_strlenc(const char *str, char *del)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != del[0] && str[i + 1] != del[1] && str[i] != del[0])
		i++;
	return (i);
}

static int	count_split(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str != NULL && *str != '\0')
    {
        str = ft_strnstr(str, " | ", strlen(str));
        if (str != NULL)
            str +=3;
        count++;
    }
	return (count);
}

static char	**ft_freemem(char **split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	split = (char **)malloc ((count_split(s, c) + 1) * 8);
	if (!split)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			split[i] = malloc(ft_strlenc(s, c) + 1);
			if (!split[i])
				return (ft_freemem(split, i));
			j = 0;
			while (*s != c && *s)
				split[i][j++] = *s++;
			split[i++][j] = 0;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}




 #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

// int	main()
// {
// 	int i;
// 	char	str[] = ",,,,,,,,sasa,,,,,,with,hipoh,gggghgssshggghhg,,,,,,,";
// 	char	**res = ft_split(str, ',');

// 	if (!res)
// 	{
// 		write(1, "Error: ft_split failed\n", 24);
// 		return (1);
// 	}
// 	i = 0;
// 	while (res[i])
// 	{
// 		printf( "%s\n", res[i]);
// 		i++;
// 	}
// 	printf("%s \n", res[i]);
// 	ft_freemem(res, i);
// 	free(res);
// 	return (0);
// }


int main()
{
    printf("%d\n", count_split("hhhh | hhhh | kkkkkkkk | uuuuuu | "));
}
