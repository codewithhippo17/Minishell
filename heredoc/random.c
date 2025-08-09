/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elhaiba hamza <ehamza@student.1337.ma>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 18:41:33 by elhaiba hamza     #+#    #+#             */
/*   Updated: 2025/08/09 18:41:35 by elhaiba hamza    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (perror("open"), NULL);
	if (read(random_fd, buffer, LEN_RANDOM) != LEN_RANDOM)
		return (perror("read"), close(random_fd), NULL);
	close(random_fd);
	filename = my_alloc(LEN_RANDOM + 1, SCOPE_TEMP);
	while (i < LEN_RANDOM)
	{
		filename[i] = charset[buffer[i] % sizeof(charset)];
		i++;
	}
	filename[LEN_RANDOM - 1] = '\0';
	return (filename);
}
