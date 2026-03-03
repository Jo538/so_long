/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:36 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 17:26:12 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(char **map)
{
	int	last_row;
	int	len;
	int	i;

	last_row = 0;
	len = ft_strlen(map[0]);
	while (map[last_row])
		last_row++;	
	i = 0;
	while (i < len)
	{
		if (map[0][i] != '1' || map[last_row - 1][i] != '1')
			return (1);			
		i++;
	}
	i = 1;
	while (i < last_row - 1)
	{
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (1);			
		i++;
	}
	return (0);
}

static char	**copy_map(char **map)
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

static int	*find_p_coords(char **map)
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
	if (map[row, col] == 'F' || map[row, col] == '1')
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
