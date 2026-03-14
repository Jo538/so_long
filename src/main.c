/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:08:44 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/14 14:23:29 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int		err;
	char	**map;

	map = NULL;
	if (argc != 2)
		error(ERR_ARGS, NULL, NULL);
	if (map_name(argv[1]))
		error(ERR_MAP_NAME, NULL, NULL);
	map = map_to_tab(argv[1]);
	if (!map)
		error(ERR_MALLOC, NULL, NULL);
	if (map_is_rectangular(map))
		error(ERR_MAP_SHAPE, map, NULL);
	if (check_collectibles(map))
		error(ERR_TILE, map, NULL);
	if (check_walls(map))
		error(ERR_WALLS, map, NULL);
	err = check_path(map);
	if (err)
		error(err, map, NULL);
	init_frame(map);
}
