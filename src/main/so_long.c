/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/05/03 19:05:03 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../map_load/map_load.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		printf("provide valid path as argument\n");
		return (1);
	}
	map = map_load(argv[1]);
	if (!map)
	{
		printf("%s map failed to load\n", argv[1]);
		return (1);
	}
	for (int i = 0; map->map[i]; i++)
 		printf ("%s\n", map->map[i]);
	map_free(map);
}