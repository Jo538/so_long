/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:45:35 by admin             #+#    #+#             */
/*   Updated: 2026/02/27 16:19:12 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ERR_ARGS "Incorrect number of arguments"
# define ERR_EXT "Invalid file name for .ber map"

# include <stdio.h>
# include <unistd.h>
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"

void	error(char *msg, int exit_code);
void	map_name(char *map);

#endif