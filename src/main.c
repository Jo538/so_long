/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:08:44 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/09 10:36:11 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	int		err;
	char	**map;

	map = NULL;
	if (argc != 2)
		error(ERR_ARGS, NULL);
	if (map_name(argv[1]))
		error(ERR_MAP_NAME, NULL);
	map = map_to_tab(argv[1]);
	if (!map)
		error(ERR_MALLOC, NULL);
	if (map_is_rectangular(map))
		error(ERR_MAP_SHAPE, map);
	if (check_collectibles(map))
		error(ERR_TILE, map);
	if (check_walls(map))
		error(ERR_WALLS, map);
	err = check_path(map);
	if (err)
		error(err, map);
	init_frame(map);
}
