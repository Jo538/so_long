/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:41:11 by admin             #+#    #+#             */
/*   Updated: 2026/03/02 10:53:20 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_RUNNER_H
# define TEST_RUNNER_H

# include "so_long.h"

extern int	tests_run;
extern int	tests_passed;

# define TEST_ASSERT(condition, msg) do {        \
      tests_run++;                                \
      if (condition) {                            \
          printf("PASS: %s\n", msg);             \
          tests_passed++;                         \
      } else {                                    \
          printf("FAIL: %s (line %d)\n", msg, __LINE__); \
      }                                           \
  } while(0)

void test_map_name(void);
#endif