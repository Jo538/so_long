/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:36 by admin             #+#    #+#             */
/*   Updated: 2026/03/14 15:35:17 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_collectibles(char **map)
{
	int			i;
	int			j;
	static int	count[3] = {0};

	i = 0;
	if (check_incorrect_collectibles(map))
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				count[0]++;
			if (map[i][j] == 'E')
				count[1]++;
			if (map[i][j] == 'C')
				count[2]++;
			j++;
		}
		i++;
	}
	if (count[0] != 1 || count[1] != 1 || count[2] < 1)
		return (1);
	return (0);
}

int	check_incorrect_collectibles(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C'
				&& map[i][j] != '0' && map[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

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
