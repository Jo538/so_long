/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:41:11 by admin             #+#    #+#             */
/*   Updated: 2026/03/04 16:42:03 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# include "so_long.h"

extern int	tests_run;
extern int	tests_passed;

# define TEST_ASSERT(actual, expected, msg) do {        \
      tests_run++;                                \
      if (actual == expected) {                            \
          printf("PASS: %s\n", msg);             \
          tests_passed++;                         \
      } else {                                    \
          printf("FAIL: %s (line %d)\n", msg, __LINE__); \
          printf("Actual: %d\n", actual);          \
          printf("Expected: %d\n", expected);        \
      }                                           \
  } while(0)

void test_map_name(void);
void test_map_to_tab(void);
void test_map_is_rectangular(void);
void test_check_collectibles(void);
void test_check_walls(void);
void test_find_p_coords(void);
void test_copy_map(void);
void test_flood_fill(void);
void test_scan_flood_fill(void);
void test_check_path(void);

// static functions
int	*find_p_coords(char **map);
char **copy_map(char **map);
void flood_fill(char **map, int row, int col, char sprite);
int	scan_flood_fill_output(char **map, char sprite);

#endif