/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:02:12 by jchartie          #+#    #+#             */
/*   Updated: 2026/02/11 21:28:58 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_u(unsigned int n)
{
	int				count;
	unsigned char	c;

	count = 0;
	if (n >= 10)
		count += printf_u(n / 10);
	c = (char)(n % 10) + '0';
	write(2, &c, 1);
	return (count + 1);
}
/*
int main(void)
{
	long n = -450;
	printf("\n%d\n", printf("%u", n));
	printf("\n%d\n", printf_u(n));
}*/
