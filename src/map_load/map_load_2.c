/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:04:47 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/12 22:36:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_struct.h"



void	free_tiles(t_map *map)
{
	int		i;
	int		j;
	t_tile	**matrix;

	matrix = map->tiles;
	i = 0;
	while ((matrix)[i])
	{
		j = 0;
		while (j < map->width)
		{
			ft_lstclear(&((matrix)[i][j]).entity_list, free);
			j++;
		}
		free((matrix)[i]);
		i++;
	}
	map->tiles = NULL;
}
