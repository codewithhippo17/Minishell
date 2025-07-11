/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:10:23 by marvin            #+#    #+#             */
/*   Updated: 2025/06/02 11:10:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nn;

	nn = n;
	if (nn < 0)
	{
		ft_putchar_fd('-', fd);
		nn *= -1;
	}
	if (nn > 9)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putnbr_fd(nn % 10, fd);
	}
	else
		ft_putchar_fd(nn + '0', fd);
}
