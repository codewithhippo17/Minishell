/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:59:33 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/07 01:08:12 by ehamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"
#include <stdio.h>
#include <unistd.h>
# define LEN_RANDOM 8
char	*ft_random(void)
{
	int		random_fd;
	char	*filename;
	char	*buffer;
	int		i;
	char	*charset;

	i = 0;
    charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd < 0)
		return (perror("open /dev/urandom"), NULL);
	if (read(random_fd, buffer, LEN_RANDOM) != LEN_RANDOM)
		return (perror("open /dev/urandom"), NULL);
	filename = malloc(LEN_RANDOM);
	if (!filename)
		return (perror("malloc"), NULL);
	while (i < LEN_RANDOM)
	{
		filename[i] = charset[buffer[i] % sizeof(charset)];
        i++;
	}
    return (filename);
}

int main()
{
    printf("%s\n", ft_random());
}
