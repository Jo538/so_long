/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:59:34 by admin             #+#    #+#             */
/*   Updated: 2026/02/27 17:19:16 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "test_runner.h"

void test_map_name(void)
{
	TEST_ASSERT(map_name(NULL), "No map name: NULL");
	TEST_ASSERT(map_name(""), "Map name is empty: \"\"");
	TEST_ASSERT(map_name("map.berr"), "Extension is too long: map.berr");
	TEST_ASSERT(map_name("map"), "No extension: map");
	TEST_ASSERT(map_name("map."), "No extension: map.");
	TEST_ASSERT(map_name(".ber"), "Map name only contains extension: .ber");
	TEST_ASSERT(!map_name("map.ber"), "Valid map name: map.ber");
}