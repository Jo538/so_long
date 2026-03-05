/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:45:35 by admin             #+#    #+#             */
/*   Updated: 2026/03/05 18:01:00 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 64

# define ERR_ARGS "Incorrect number of arguments"
# define ERR_MAP_NAME "Invalid file name for .ber map"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

typedef struct s_game
{
	int		width;
	int		height;
	void	*mlx;
	void	*window;
	void	*grass;
	void	*dog;
	void	*bread;
	void	*tree;
	void	*exit;
	char	**map;
}	t_game;


void	error(char *msg, int exit_code);
void	free_tab(char **tab);
int		map_name(char *map);
char	**map_to_tab(char *map_name);
int		map_is_rectangular(char **map);
int		check_collectibles(char **map);
int		check_walls(char **map);
int		check_path(char **map);
void	init_frame(char **map);
#endif