/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 16:16:15 by admin             #+#    #+#             */
/*   Updated: 2026/03/03 15:06:53 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "test_runner.h"

int	tests_run;
int	tests_passed;

int main(void)
{
	printf("%s", "--------------TEST VALID MAP NAME--------------\n\n");
	test_map_name();
	printf("\n\n%s", "--------------TEST MAP GETS CONVERTED TO 2D ARRAY--------------\n\n");
	test_map_to_tab();
	printf("\n\n%s", "--------------TEST MAP IS RECTANGULAR--------------\n\n");
	test_map_is_rectangular();
	printf("\n\n%s", "--------------TEST MAP RULES ON P + E + C--------------\n\n");	
	test_check_collectibles();
	printf("\n\n%s", "--------------TEST MAP SURROUNDED BY WALLS--------------\n\n");
	test_check_walls();
}