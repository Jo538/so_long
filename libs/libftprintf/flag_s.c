/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:06:41 by jchartie          #+#    #+#             */
/*   Updated: 2026/02/11 21:28:54 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printf_s(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}
/*
int main(void)
{
	char *str = NULL;
	printf("\n%d\n", printf_s(str));
}*/