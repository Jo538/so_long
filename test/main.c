/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:16:15 by admin             #+#    #+#             */
/*   Updated: 2026/03/02 12:08:17 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "test_runner.h"

int	tests_run;
int	tests_passed;

int main(void)
{
	test_map_name();
	printf("%c\n", '\n');
	test_map_to_tab();
	
}