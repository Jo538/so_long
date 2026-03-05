/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 17:00:04 by admin             #+#    #+#             */
/*   Updated: 2026/03/05 18:26:36 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_window_size(char **map, t_game *game)
{
	int	height;

	height = 0;
	game->width = TILE_SIZE*ft_strlen(map[0]);
	while (map[height])
		height++;
	game->height = TILE_SIZE*height;
}

static void	setup(char **map, t_game *game)
{
	int		w;
	int		h;
	
	game->map = map;
	game->grass = mlx_xpm_file_to_image(game->mlx, "textures/grass.xpm", &w, &h);
	game->tree = mlx_xpm_file_to_image(game->mlx, "textures/tree.xpm", &w, &h);
	game->dog = mlx_xpm_file_to_image(game->mlx, "textures/dog.xpm", &w, &h);
	game->bread = mlx_xpm_file_to_image(game->mlx, "textures/bread.xpm", &w, &h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &w, &h);
}

static void	create_initial_frame(t_game game)
{
	int	i;
	int	j;

	i = 0;
	while (i < (game.height / TILE_SIZE))
	{
		j = 0;
		while (j < (game.width/ TILE_SIZE))
		{
			if (game.map[i][j] == '0')
				mlx_put_image_to_window(game.mlx, game.window, game.grass, j*TILE_SIZE, i*TILE_SIZE);
			if (game.map[i][j] == 'P')
				mlx_put_image_to_window(game.mlx, game.window, game.dog, j*TILE_SIZE, i*TILE_SIZE);
			if (game.map[i][j] == '1')
				mlx_put_image_to_window(game.mlx, game.window, game.tree, j*TILE_SIZE, i*TILE_SIZE);
			if (game.map[i][j] == 'C')
				mlx_put_image_to_window(game.mlx, game.window, game.bread, j*TILE_SIZE, i*TILE_SIZE);
			if (game.map[i][j] == 'E')
				mlx_put_image_to_window(game.mlx, game.window, game.exit, j*TILE_SIZE, i*TILE_SIZE);
			j++;
		}
		i++;
	}

	
}

void	init_frame(char **map)
{
	t_game	game;

	get_window_size(map, &game);

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, game.width, game.height, "Pollux's Game");

	create_initial_frame(game);

	mlx_loop(game.mlx);
}