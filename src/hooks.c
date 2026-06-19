/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:36:56 by admin             #+#    #+#             */
/*   Updated: 2026/03/17 18:03:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		on_close(param);
	if (keycode == KEY_W)
		move_up(game);
	if (keycode == KEY_S)
		move_down(game);
	if (keycode == KEY_A)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
	return (0);
}

int	on_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->map)
		free_tab(game->map);
	if (game->grass)
		mlx_destroy_image(game->mlx, game->grass);
	if (game->dog)
		mlx_destroy_image(game->mlx, game->dog);
	if (game->bread)
		mlx_destroy_image(game->mlx, game->bread);
	if (game->tree)
		mlx_destroy_image(game->mlx, game->tree);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	// mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}
