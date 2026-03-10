/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 09:36:56 by admin             #+#    #+#             */
/*   Updated: 2026/03/10 10:10:23 by jchartie         ###   ########.fr       */
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
	if (keycode == KEY_A)
		move_down(game);
	if (keycode == KEY_S)
		move_left(game);
	if (keycode == KEY_D)
		move_right(game);
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
