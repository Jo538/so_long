/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 18:32:37 by admin             #+#    #+#             */
/*   Updated: 2026/03/05 18:51:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "test_runner.h"

void test_get_window_size(void)
{
	char **map;
	t_game game = {0};
	
	char *case_a[] = {"11111", "1P0C1", "10E01", "11111", NULL};
	map = case_a;
	get_window_size(map, &game);
	TEST_ASSERT(game.width, 5, "Width should be 5 columns");
	TEST_ASSERT(game.height, 4, "Height should be 4 rows");

	char *case_b[] = {"111", "1P0", "10E", "111", "111", NULL};
	map = case_b;
	get_window_size(map, &game);
	TEST_ASSERT(game.width, 3, "Width should be 3 columns");
	TEST_ASSERT(game.height, 5, "Height should be 5 rows");
}