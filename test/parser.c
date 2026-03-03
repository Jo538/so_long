/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:59:34 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 11:42:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "test_runner.h"

void test_map_name(void)
{
	TEST_ASSERT(map_name(NULL), 1, "No map name: NULL");
	TEST_ASSERT(map_name(""), 1, "Map name is empty: \"\"");
	TEST_ASSERT(map_name("map.berr"), 1, "Extension is too long: map.berr");
	TEST_ASSERT(map_name("map"), 1, "No extension: map");
	TEST_ASSERT(map_name("map."), 1, "No extension: map.");
	TEST_ASSERT(map_name(".ber"), 1, "Map name only contains extension: .ber");
	TEST_ASSERT(map_name("map.ber"), 0, "Valid map name: map.ber");
}

void test_map_to_tab(void)
{
	char	**map;
	
	map = map_to_tab("test/maps/5x3.ber");
	TEST_ASSERT(ft_strncmp(map[0], "11111", ft_strlen("11111")), 0, "line 1 should be 11111");
	TEST_ASSERT(ft_strncmp(map[1], "1P0C1", ft_strlen("1P0C1")), 0, "line 2 should be 1P0C1");
	TEST_ASSERT(ft_strncmp(map[2], "11111", ft_strlen("11111")), 0, "line 3 should be 11111");
	free_tab(map);

	map = map_to_tab(NULL);
	TEST_ASSERT(map == NULL, 1, "NULL input returns NULL");

	map = map_to_tab("test/maps/1x1.ber");
	TEST_ASSERT(ft_strncmp(map[0], "A", ft_strlen("A")), 0, "1x1: line 1 should be A");
	TEST_ASSERT(map[1] == NULL, 1, "1x1: array should be NULL-terminated");
	free_tab(map);

	map = map_to_tab("test/maps/1x5.ber");
	TEST_ASSERT(ft_strncmp(map[0], "ABCDE", ft_strlen("ABCDE")), 0, "1x5: line 1 should be ABCDE");
	TEST_ASSERT(map[1] == NULL, 1, "1x5: array should be NULL-terminated");
	free_tab(map);

	map = map_to_tab("test/maps/5x5.ber");
	TEST_ASSERT(ft_strncmp(map[0], "11111", ft_strlen("11111")), 0, "5x5: line 1 should be 11111");
	TEST_ASSERT(ft_strncmp(map[1], "1AAA1", ft_strlen("1AAA1")), 0, "5x5: line 2 should be 1AAA1");
	TEST_ASSERT(ft_strncmp(map[2], "1BBB1", ft_strlen("1BBB1")), 0, "5x5: line 3 should be 1BBB1");
	TEST_ASSERT(ft_strncmp(map[3], "1CCC1", ft_strlen("1CCC1")), 0, "5x5: line 4 should be 1CCC1");
	TEST_ASSERT(ft_strncmp(map[4], "11111", ft_strlen("11111")), 0, "5x5: line 5 should be 11111");
	TEST_ASSERT(map[5] == NULL, 1, "5x5: array should be NULL-terminated");
	free_tab(map);

	map = map_to_tab("test/maps/12x15.ber");
	TEST_ASSERT(ft_strncmp(map[0], "111111111111", ft_strlen("111111111111")), 0, "12x15: line 1 should be top wall");
	TEST_ASSERT(ft_strncmp(map[1], "1AAAAAAAAAA1", ft_strlen("1AAAAAAAAAA1")), 0, "12x15: line 2 should be 1AAAAAAAAAA1");
	TEST_ASSERT(ft_strncmp(map[14], "111111111111", ft_strlen("111111111111")), 0, "12x15: line 15 should be bottom wall");
	TEST_ASSERT(map[15] == NULL, 1, "12x15: array should be NULL-terminated");
	free_tab(map);

	map = map_to_tab("test/maps/15x7.ber");
	TEST_ASSERT(ft_strncmp(map[0], "111111111111111", ft_strlen("111111111111111")), 0, "15x7: line 1 should be top wall");
	TEST_ASSERT(ft_strncmp(map[1], "1AAAAAAAAAAAAA1", ft_strlen("1AAAAAAAAAAAAA1")), 0, "15x7: line 2 should be 1AAAAAAAAAAAAA1");
	TEST_ASSERT(ft_strncmp(map[6], "111111111111111", ft_strlen("111111111111111")), 0, "15x7: line 7 should be bottom wall");
	TEST_ASSERT(map[7] == NULL, 1, "15x7: array should be NULL-terminated");
	free_tab(map);

	map = map_to_tab("test/maps/empty_first_row.ber");
	TEST_ASSERT(ft_strncmp(map[0], "A", ft_strlen("A")), 0, "empty_first_row: ft_split skips empty row, line 1 should be A");
	TEST_ASSERT(map[1] == NULL, 1, "empty_first_row: array should be NULL-terminated");
	free_tab(map);
}

void	test_map_is_rectangular(void)
{
	char **map;

	// map is rectangular 3x5
	char *case_a[] = {"11111", "1P0C1", "11111", NULL};
	map = case_a;
	TEST_ASSERT(map_is_rectangular(map), 0, "3x5 map is rectangular");

	// map is rectangular 5x3
	char *case_b[] = {"111", "1P0", "111", "234", "ABC", NULL};
	map = case_b;
	TEST_ASSERT(map_is_rectangular(map), 0, "5x3 map is rectangular");

	// row 3 is shorter than other rows
	char *case_c[] = {"111", "1P0", "11", "234", "ABC", NULL};
	map = case_c;
	TEST_ASSERT(map_is_rectangular(map), 1, "row three is shorter than other rows");

	// row 3 is longer than other rows
	char *case_d[] = {"111", "1P0", "1111", "234", "ABC", NULL};
	map = case_d;
	TEST_ASSERT(map_is_rectangular(map), 1, "row three is longer than other rows");

	// map is squared
	char *case_e[] = {"111", "1P0", "111", NULL};
	map = case_e;
	TEST_ASSERT(map_is_rectangular(map), 1, "map is squared");
}

