/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:44:49 by admin             #+#    #+#             */
/*   Updated: 2026/03/02 16:38:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_name(char *map)
{
	int	len;

	if (!map || !map[0])
		return (1);
	len = ft_strlen(map);
	if (len <= 4)
		return (1);
	len = len - 4;
	if (!map[len] || ft_strncmp(map + len, ".ber", 4) != 0)
		return (1);
	return (0);
}

static char	*extract_one_line_map(int fd)
{
	char	*old_line;
	char	*new_line;
	char	*temp;

	new_line = get_next_line(fd);
	if (!new_line)
		return (NULL);
	temp = "Init";
	while (temp)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		old_line = new_line;
		new_line = ft_strjoin(old_line, temp);
		free(temp);
		free(old_line);
	}
	return (new_line);
}

// open map + extract first line of map
char	**map_to_tab(char *map_name)
{
	int		fd;
	char	*line;
	char	**map;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = extract_one_line_map(fd);
	map = ft_split(line, '\n');
	free(line);
	close(fd);
	return (map);
}
