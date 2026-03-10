/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:09:55 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/10 14:35:53 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (game->map[y - 1][x] == '1')
		return ;
	if (game->collectibles > 0 && game->map[y - 1][x] == 'E')
		return ;
	if (game->collectibles <= 0 && game->map[y - 1][x] == 'E')
		on_close(game);
	if (game->map[y - 1][x] == 'C')
		game->collectibles--;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x * TILE_SIZE,
		y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, x * TILE_SIZE,
		(y - 1) * TILE_SIZE);
	game->coords_p[0]--;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_down(t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (game->map[y + 1][x] == '1')
		return ;
	if (game->collectibles > 0 && game->map[y + 1][x] == 'E')
		return ;
	if (game->collectibles <= 0 && game->map[y + 1][x] == 'E')
		on_close(game);
	if (game->map[y + 1][x] == 'C')
		game->collectibles--;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x * TILE_SIZE,
		y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, x * TILE_SIZE,
		(y + 1) * TILE_SIZE);
	game->coords_p[0]++;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_left(t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (game->map[y][x - 1] == '1')
		return ;
	if (game->collectibles > 0 && game->map[y][x - 1] == 'E')
		return ;
	if (game->collectibles <= 0 && game->map[y][x - 1] == 'E')
		on_close(game);
	if (game->map[y][x - 1] == 'C')
		game->collectibles--;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x * TILE_SIZE,
		y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, (x - 1)
		* TILE_SIZE, y * TILE_SIZE);
	game->coords_p[1]--;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_right(t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (game->map[y][x + 1] == '1')
		return ;
	if (game->collectibles > 0 && game->map[y][x + 1] == 'E')
		return ;
	if (game->collectibles <= 0 && game->map[y][x + 1] == 'E')
		on_close(game);
	if (game->map[y][x + 1] == 'C')
		game->collectibles--;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x * TILE_SIZE,
		y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, (x + 1)
		* TILE_SIZE, y * TILE_SIZE);
	game->coords_p[1]++;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}
