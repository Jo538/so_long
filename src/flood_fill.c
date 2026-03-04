/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:18:23 by admin             #+#    #+#             */
/*   Updated: 2026/03/04 14:14:24 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#ifdef TESTING
char	**copy_map(char **map)
#else
static char	**copy_map(char **map)
#endif
{
	int		rows;
	int		i;
	char	**tmp_map;
	
	rows = 0;
	while (map[rows])
		rows++;
	tmp_map = ft_calloc(rows, sizeof(char *));
	if (!tmp_map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		tmp_map[i] = ft_strdup(map[i]);
		if (!tmp_map[i])
			return (free_tab(tmp_map), NULL);
		i++;
	}
	return (tmp_map);
}

#ifdef TESTING
int	*find_p_coords(char **map)
#else
static int	*find_p_coords(char **map)
#endif
{
	int	row;
	int	col;
	int	*coords;

	row = 1;
	coords = ft_calloc(2, sizeof(int));
	if (!coords)
		return (NULL);
	while (map[row])
	{
		col = 1;
		while (map[row][col])
		{
			if (map[row][col] == 'P')
			{
				coords[0] = row;
				coords[1] = col;
				return (coords);
			}
			col++;
		}
		row++;
	}
	return (coords);
}

static void	flood_fill(char **map, int row, int col)
{
	if (map[row][col] == 'F' || map[row][col] == '1')
		return ;
	map[row][col] = 'F';
	flood_fill(map, row + 1, col);
	flood_fill(map, row - 1, col);
	flood_fill(map, row, col + 1);
	flood_fill(map, row, col - 1);
}

static int	scan_flood_fill_output(char **map)
{
	int	row;
	int	col;
	
	row = 1;
	while (map[row])
	{
		col = 1;
		while (map[row][col])
		{
			if (map[row][col] == 'E' || map[row][col] == 'C')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	check_path(char **map)
{
	int		*coords_p;
	char	**map_bis;
	int		row_p;
	int		col_p;

	coords_p = find_p_coords(map);
	row_p = coords_p[0];
	col_p = coords_p[1];
	free(coords_p);
	map_bis = copy_map(map);
	flood_fill(map_bis, row_p, col_p);
	if (scan_flood_fill_output(map_bis))
		return (free_tab(map_bis), 1);
	return (free_tab(map_bis), 0);
}
