/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchartie <jchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:44:49 by admin             #+#    #+#             */
/*   Updated: 2026/03/09 11:20:57 by jchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_name(char *map)
{
	int		start;
	int		len;
	char	*ptr;

	if (!map || !map[0])
		return (1);
	ptr = ft_strrchr(map, '/');
	if (!ptr)
		start = 0;
	else
		start = ptr - map + 1;
	len = ft_strlen(map);
	if (len - start <= 4)
		return (1);
	len = len - 4;
	if (!map[len] || ft_strncmp(map + len, ".ber", 4) != 0)
		return (1);
	return (0);
}

static char	*extract_one_line_map(int fd, int *err)
{
	char	*old_line;
	char	*new_line;
	char	*temp;

	new_line = get_next_line(fd);
	if (!new_line)
		return (*err = ERR_MAP_EMPTY, NULL);
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
		if (!new_line)
			return (*err = ERR_MALLOC, NULL);
	}
	return (new_line);
}

char	**map_to_tab(char *map_name)
{
	int		fd;
	int		err;
	char	*line;
	char	**map;

	err = -1;
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		error(ERR_FILE, NULL);
	line = extract_one_line_map(fd, &err);
	if (!line)
	{
		close(fd);
		error(err, NULL);
	}
	map = ft_split(line, '\n');
	free(line);
	close(fd);
	return (map);
}

int	map_is_rectangular(char **map)
{
	int	length;
	int	width;
	int	i;

	length = ft_strlen(map[0]);
	width = 0;
	while (map[width])
		width++;
	if (length == width)
		return (1);
	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != length)
			return (1);
		i++;
	}
	return (0);
}

int	check_collectibles(char **map)
{
	int	i;
	int	j;
	int	count[3] = {0};

	i = 0;
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
