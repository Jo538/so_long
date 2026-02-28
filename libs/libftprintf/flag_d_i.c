/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:53:37 by jchartie          #+#    #+#             */
/*   Updated: 2025/12/03 14:24:05 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_d_i(int n, int fd)
{
	long	nb;
	char	c;
	int		count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
		count++;
	}
	if (nb >= 10)
		count += printf_d_i((int)(nb / 10), fd);
	c = '0' + (nb % 10);
	write(fd, &c, 1);
	return (count + 1);
}
