/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:59:34 by admin             #+#    #+#             */
/*   Updated: 2026/03/02 11:12:10 by admin            ###   ########.fr       */
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
