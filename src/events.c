/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:36:56 by admin             #+#    #+#             */
/*   Updated: 2026/03/06 18:01:40 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_vertical(int direction, t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (direction == 1)
		if (game->map[y - 1][x] == '1')
			return ;
	if (direction == -1)
		if (game->map[y + 1][x] == '1')
			return ;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	if (direction == 1)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->dog, x*TILE_SIZE, (y - 1)*TILE_SIZE);
		game->coords_p[0]--; 		
	}
	if (direction == -1)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->dog, x*TILE_SIZE, (y + 1)*TILE_SIZE);
		game->coords_p[0]++; 		
	}
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

static void	move_horizontal(int direction, t_game *game)
{
	int	x;
	int	y;

	x = game->coords_p[1];
	y = game->coords_p[0];
	if (direction == -1)
		if (game->map[y][x - 1] == '1')
			return ;
	if (direction == 1)
		if (game->map[y][x + 1] == '1')
		return ;
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	if (direction == -1)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->dog, (x - 1)*TILE_SIZE, y*TILE_SIZE);
		game->coords_p[1]--;		
	}
	if (direction == 1)
	{
		mlx_put_image_to_window(game->mlx, game->window, game->dog, (x + 1)*TILE_SIZE, y*TILE_SIZE);
		game->coords_p[1]++; 		
	}
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

int	on_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;

	if (keycode == KEY_ESC)
		on_close(param);
	if (keycode == KEY_W)
		move_vertical(1, game);
	if (keycode == KEY_A)
		move_vertical(-1, game);
	if (keycode == KEY_S)
		move_horizontal(-1, game);
	if (keycode == KEY_D)
		move_horizontal(1, game);
	return (0);
}

int	on_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;

	free_tab(game->map);
	mlx_destroy_image(game->mlx, game->grass);
	mlx_destroy_image(game->mlx, game->dog);
	mlx_destroy_image(game->mlx, game->bread);
	mlx_destroy_image(game->mlx, game->tree);
	mlx_destroy_image(game->mlx, game->exit);
	mlx_destroy_window(game->mlx, game->window);
	#ifndef __APPLE__
		mlx_destroy_display(game->mlx);
	#endif
	free(game->mlx);
	exit(EXIT_SUCCESS);
}
