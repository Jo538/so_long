/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:41:34 by admin             #+#    #+#             */
/*   Updated: 2026/03/10 11:11:41 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_match(const char *s)
{
	char	*s2;
	int		i;

	if (!s)
		return (-1);
	s2 = "cspdiuxX";
	i = 0;
	while (s2[i])
	{
		if (ft_strncmp(s, &s2[i], 1) == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

static int	handler(char c, va_list args)
{
	unsigned long int	ptr;
	int					count;

	count = 0;
	if (c == 'c')
		count += printf_c(va_arg(args, int));
	if (c == 's')
		count += printf_s(va_arg(args, char *));
	if (c == 'd' || c == 'i')
		count += printf_d_i(va_arg(args, int), 1);
	if (c == 'u')
		count += printf_u(va_arg(args, unsigned int));
	if (c == 'p')
	{
		ptr = va_arg(args, unsigned long int);
		if (ptr != 0)
		{
			write(1, "0x", 2);
			count += 2;
		}
		count += printf_p(ptr);
	}
	if (c == 'x' || c == 'X')
		count += printf_x(va_arg(args, unsigned int), c);
	return (count);
}

static int	traverse(const char *s, va_list args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '%' && s[i + 1] == '%')
		{
			write(1, &s[i], 1);
			i += 2;
			count++;
			continue ;
		}
		if (s[i] == '%' && ft_match(s + i + 1) == 1)
		{
			count += handler(s[i + 1], args);
			i += 2;
			continue ;
		}
		write(1, &s[i], 1);
		i++;
		count++;
	}
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	if (!s)
		return (-1);
	va_start(args, s);
	count = traverse(s, args);
	return (count);
}
