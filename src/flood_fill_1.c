/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:18:23 by admin             #+#    #+#             */
/*   Updated: 2026/03/10 10:21:28 by jchartie         ###   ########.fr       */
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
	tmp_map = ft_calloc(rows + 1, sizeof(char *));
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
	tmp_map[i] = NULL;
	return (tmp_map);
}

#ifdef TESTING
void	find_p_coords(char **map, int *coords)
#else
void	find_p_coords(char **map, int *coords)
#endif
{
	int	row;
	int	col;

	row = 1;
	while (map[row])
	{
		col = 1;
		while (map[row][col])
		{
			if (map[row][col] == 'P')
			{
				coords[0] = row;
				coords[1] = col;
			}
			col++;
		}
		row++;
	}
}

#ifdef TESTING
void	flood_fill(char **map, int row, int col, char sprite)
#else
static void	flood_fill(char **map, int row, int col, char sprite)
#endif
{
	if (sprite == 'C')
	{
		if (map[row][col] == 'F' || map[row][col] == '1' || map[row][col] == 'E')
			return ;
	}
	if (sprite == 'E')
	{
		if (map[row][col] == 'F' || map[row][col] == '1')
			return ;
	}
	map[row][col] = 'F';
	flood_fill(map, row + 1, col, sprite);
	flood_fill(map, row - 1, col, sprite);
	flood_fill(map, row, col + 1, sprite);
	flood_fill(map, row, col - 1, sprite);
}

static int	flood_fill_loop(char **map, int *coords, char sprite)
{
	int		row_p;
	int		col_p;
	char	**map_bis;

	row_p = coords[0];
	col_p = coords[1];
	map_bis = copy_map(map);
	if (!map_bis)
		return (ERR_MALLOC);
	flood_fill(map_bis, row_p, col_p, sprite);
	if (scan_flood_fill_output(map_bis, sprite))
	{
		free_tab(map_bis);
		return (ERR_PATH);
	}
	free_tab(map_bis);
	return (0);
}

int	check_path(char **map)
{
	int		err;
	int		coords_p[2] = {0};

	find_p_coords(map, coords_p);
	err = flood_fill_loop(map, coords_p, 'C');
	if (err)
		return (err);
	err = flood_fill_loop(map, coords_p, 'E');
	if (err)
		return (err);
	return (0);
}
