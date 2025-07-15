/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamza <ehamza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:59:33 by ehamza            #+#    #+#             */
/*   Updated: 2025/07/15 10:51:16 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/heredoc.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_random(void)
{
	int		random_fd;
	char	*filename;
	char	buffer[LEN_RANDOM];
	int		i;
	char	*charset;

	i = 0;
	charset = "r8f5b6h46scw9";
	random_fd = open("/dev/urandom", O_RDONLY);
	if (random_fd < 0)
		return (perror("open /dev/urandom"), NULL);
	if (read(random_fd, buffer, LEN_RANDOM) != LEN_RANDOM)
		return (perror("read /dev/urandom"), NULL);
	close(random_fd);
	filename = malloc(LEN_RANDOM + 1);
	if (!filename)
		return (perror("malloc"), NULL);
	while (i < LEN_RANDOM)
	{
		filename[i] = charset[buffer[i] % sizeof(charset)];
		i++;
	}
	filename[LEN_RANDOM - 1] = '\0';
	return (filename);
}

/*int main()
{
	char *random_filename = ft_random();
	printf("%s\n", random_filename);
	free(random_filename);
}*/
