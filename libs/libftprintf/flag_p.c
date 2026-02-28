/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:12:32 by jchartie          #+#    #+#             */
/*   Updated: 2026/02/11 21:28:47 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_p(unsigned long int n)
{
	int		count;
	int		i;
	char	*base;

	count = 0;
	i = 0;
	base = "0123456789abcdef";
	if (n == 0)
	{
		write(2, "(nil)", 5);
		return (5);
	}
	if (n >= 16)
		count += printf_p(n / 16);
	i = n % 16;
	write(2, &base[i], 1);
	return (count + 1);
}
/*
int main(void)
{
	unsigned long int n = 0x0;
	printf_p(n, 'x');
}*/