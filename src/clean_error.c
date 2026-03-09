/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:41:21 by admin             #+#    #+#             */
/*   Updated: 2026/03/09 10:37:42 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error(int error_code, char **map)
{
	static char	*msg[] = {
		"Incorrect number of arguments",
		"Invalid map name. Follow map.ber format",
		"Invalid map shape. The map should be rectangular",
		"The map is empty",
		"Allocation failure",
		"P or E is duplicated",
		"P, E or C != 1",
		"Map not surrounded by walls",
		"Path to exit is not valid",
		"Could not open map file"
	};

	if (map)
		free_tab(map);
	ft_printf("Error\n%s", msg[error_code]);
	exit(1);
}
