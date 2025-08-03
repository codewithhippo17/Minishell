/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelghad <ybelghad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:28:52 by ybelghad          #+#    #+#             */
/*   Updated: 2024/11/05 00:03:29 by ybelghad         ###   ########.fr       */
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
	alpha = ft_calloc((len + 1), sizeof(char), SCOPE_TEMP);
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
