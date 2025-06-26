/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:10:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:10:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nbr(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		i++;
		nbr *= -1;
	}
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	long	len;
	char	*alpha;

	nbr = n;
	len = len_nbr(n);
	alpha = ft_calloc((len + 1), sizeof(char));
	if (!alpha)
		return (NULL);
	alpha[len] = '\0';
	if (nbr == 0)
		alpha[0] = '0';
	if (nbr < 0)
	{
		alpha[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		alpha[--len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (alpha);
}
