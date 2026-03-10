/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:00:04 by admin             #+#    #+#             */
/*   Updated: 2026/03/10 14:45:29 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_window_size(char **map, t_game *game)
{
	int	height;

	height = 0;
	game->map = map;
	game->width = ft_strlen(map[0]);
	while (map[height])
		height++;
	game->height = height;
}

static void	load_tiles(t_game *game)
{
	int	w;
	int	h;

	game->grass = mlx_xpm_file_to_image(game->mlx, "textures/grass.xpm", &w,
			&h);
	game->tree = mlx_xpm_file_to_image(game->mlx, "textures/tree.xpm", &w, &h);
	game->dog = mlx_xpm_file_to_image(game->mlx, "textures/dog.xpm", &w, &h);
	game->bread = mlx_xpm_file_to_image(game->mlx, "textures/bread.xpm", &w,
			&h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &w, &h);
}

static void	*get_tile_image(int i, int j, t_game *game)
{
	if (game->map[i][j] == 'P')
	{
		game->coords_p[0] = i;
		game->coords_p[1] = j;
		return (game->dog);
	}
	if (game->map[i][j] == '0')
		return (game->grass);
	if (game->map[i][j] == '1')
		return (game->tree);
	if (game->map[i][j] == 'C')
		return (game->bread);
	if (game->map[i][j] == 'E')
		return (game->exit);
	return (NULL);
}

static void	create_initial_frame(t_game *game)
{
	int		i;
	int		j;
	void	*tile;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			tile = get_tile_image(i, j, game);
			mlx_put_image_to_window(game->mlx, game->window, tile, j
				* TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

void	init_frame(char **map)
{
	t_game	game;

	get_window_size(map, &game);
	game.moves = 0;
	game.mlx = mlx_init();
	if (!game.mlx)
		error(ERR_MLX, map);
	game.window = mlx_new_window(game.mlx, game.width * TILE_SIZE, game.height
			* TILE_SIZE, "Pollux's Game");
	count_collectibles(map, &game);
	load_tiles(&game);
	create_initial_frame(&game);
	mlx_key_hook(game.window, on_keypress, &game);
	mlx_hook(game.window, 17, 1L << 17, on_close, &game);
	mlx_loop(game.mlx);
}
