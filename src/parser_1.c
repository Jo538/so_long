/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:44:49 by admin             #+#    #+#             */
/*   Updated: 2026/02/27 17:19:54 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_name(char *map)
{
	int	len;

	if (!map || !map[0])
		return (1);
	len = ft_strlen(map);
	if (len < 4)
		return (1);
	len = len - 4;
	if (!map[len] || ft_strncmp(map + len, ".ber", 4) != 0)
		return (1);
	return (0);
}