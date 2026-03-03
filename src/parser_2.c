/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:44:36 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 15:25:23 by admin            ###   ########.fr       */
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
