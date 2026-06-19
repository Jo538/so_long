/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:45:35 by admin             #+#    #+#             */
/*   Updated: 2026/03/17 18:06:33 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"

# define TILE_SIZE 64
# define MAX_ROWS 16
# define MAX_COLS 30

# define ERR_ARGS 0
# define ERR_MAP_NAME 1
# define ERR_MAP_SHAPE 2
# define ERR_MAP_EMPTY 3
# define ERR_MALLOC 4
# define ERR_DUPS 5
# define ERR_TILE 6
# define ERR_WALLS 7
# define ERR_PATH 8
# define ERR_FILE 9
# define ERR_MLX 10
# define ERR_MAP_SIZE 11
# define ERR_TILE_ABSENT 12

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

typedef struct s_game
{
	int		width;
	int		height;
	int		moves;
	int		collectibles;
	int		coords_p[2];
	char	**map;
	void	*mlx;
	void	*window;
	void	*grass;
	void	*dog;
	void	*bread;
	void	*tree;
	void	*exit;
}	t_game;

/* Parsing functions on map */
int		map_name(char *map);
char	**map_to_tab(char *map_name);
int		map_is_rectangular(char **map);
int		check_collectibles(char **map);
int		check_incorrect_collectibles(char **map);
int		check_walls(char **map);

/* Flood Fill to check C and E reachable */
int		check_path(char **map);
int		scan_flood_fill_output(char **map, char sprite);

/* Game display */
void	init_frame(char **map);
void	count_collectibles(char **map, t_game *game);

/* Hooks */
int		on_keypress(int keycode, void *game);
int		on_close(void *game);

/* Events */
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/* Errors and free functions */
void	error(int error_code, char **map, t_game *game);
void	free_tab(char **tab);

#endif