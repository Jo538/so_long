/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:36:56 by admin             #+#    #+#             */
/*   Updated: 2026/03/09 16:21:03 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_up(t_game *game)
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
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, x*TILE_SIZE, (y - 1)*TILE_SIZE);
	game->coords_p[0]--; 		
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

static void	move_down(t_game *game)
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
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, x*TILE_SIZE, (y + 1)*TILE_SIZE);
	game->coords_p[0]++; 		
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

static void	move_left(t_game *game)
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
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, (x - 1)*TILE_SIZE, y*TILE_SIZE);
	game->coords_p[1]--;		
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

static void	move_right(t_game *game)
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
	mlx_put_image_to_window(game->mlx, game->window, game->grass, x*TILE_SIZE, y*TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->window, game->dog, (x + 1)*TILE_SIZE, y*TILE_SIZE);
	game->coords_p[1]++; 		
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
		move_up(game);
	if (keycode == KEY_A)
		move_down(game);
	if (keycode == KEY_S)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
	printf("collectibles: %d\n", game->collectibles);
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
