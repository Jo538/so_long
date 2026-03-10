/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:30:27 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/10 11:11:22 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_x(unsigned int n, char c)
{
	int		count;
	int		i;
	char	*base1;
	char	*base2;

	count = 0;
	i = 0;
	base1 = "0123456789abcdef";
	base2 = "0123456789ABCDEF";
	if (n >= 16)
		count += printf_x(n / 16, c);
	i = n % 16;
	if (c == 'X')
		write(1, &base2[i], 1);
	else
		write(1, &base1[i], 1);
	return (count + 1);
}
/*
int main(void)
{
	unsigned long int n = 0x0;
	printf_p(n, 'x');
}*/