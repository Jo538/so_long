/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:08:44 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/05 17:53:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	char	**map;
	
	map = NULL;
	if (argc != 2)
		error(ERR_ARGS, 1);
	if (map_name(argv[1]))
		error(ERR_MAP_NAME, 1);
	map = map_to_tab(argv[1]);
	init_frame(map);
}
