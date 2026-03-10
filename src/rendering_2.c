/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:18:21 by jchartie          #+#    #+#             */
/*   Updated: 2026/03/10 10:18:52 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectibles(char **map, t_game *game)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	game->collectibles = count;
}
