/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:45:35 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 12:12:19 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ERR_ARGS "Incorrect number of arguments"
# define ERR_MAP_NAME "Invalid file name for .ber map"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

void	error(char *msg, int exit_code);
void	free_tab(char **tab);
int		map_name(char *map);
char	**map_to_tab(char *map_name);
int		map_is_rectangular(char **map);
int		check_collectibles(char **map);

#endif