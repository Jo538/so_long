/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:20:36 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/10 10:21:33 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	scan_flood_fill_output(char **map, char sprite)
{
	int	row;
	int	col;

	row = 1;
	while (map[row])
	{
		col = 1;
		while (map[row][col])
		{
			if (map[row][col] == sprite)
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}
