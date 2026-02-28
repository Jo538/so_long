/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:02:54 by admin             #+#    #+#             */
/*   Updated: 2025/12/04 12:36:06 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *s, ...);
int		printf_c(char c);
int		printf_s(char *s);
int		printf_p(unsigned long int n);
int		printf_d_i(int n, int fd);
int		printf_u(unsigned int n);
int		printf_x(unsigned int n, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif