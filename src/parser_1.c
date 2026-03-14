/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:44:49 by admin             #+#    #+#             */
/*   Updated: 2026/03/14 16:47:23 by admin            ###   ########.fr       */
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

static int	check_map_dimensions(char *line, int *err)
{
	int	start;
	int	end;
	int	rows;

	start = 0;
	end = 0;
	rows = 0;
	while (line[end])
	{
		if (end > 0 && line[end - 1] == '\n' && line[end] == '\n')
			return (*err = ERR_MAP_SHAPE, 1);
		if (line[end] == '\n')
		{
			if (end - start > MAX_COLS)
				return (*err = ERR_MAP_SIZE, 1);
			start = end + 1;
			rows++;
		}
		end++;
	}
	rows += (end > start);
	if (rows > MAX_ROWS || (end - start) > MAX_COLS)
		return (*err = ERR_MAP_SIZE, 1);
	return (0);
}

static char	*extract_one_line_map(int fd, int *err)
{
	char		*old_line;
	char		*new_line;
	static char	*temp = "Init";

	new_line = get_next_line(fd);
	if (!new_line)
		return (*err = ERR_MAP_EMPTY, NULL);
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
	if (check_map_dimensions(new_line, err))
		return (free(new_line), NULL);
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
		error(ERR_FILE, NULL, NULL);
	line = extract_one_line_map(fd, &err);
	if (!line)
	{
		close(fd);
		error(err, NULL, NULL);
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
	i = 1;
	while (map[width])
		width++;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != length)
			return (1);
		i++;
	}
	return (0);
}
