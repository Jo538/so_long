/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:41:11 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 15:00:36 by admin            ###   ########.fr       */
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
void	test_map_is_rectangular(void);
void	test_check_collectibles(void);
void test_check_walls(void);

#endif