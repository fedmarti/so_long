/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:34:05 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/28 00:39:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_struct.h"
#include "../macro_headers/general_settings.h"

//returns map coordinates from global coordinates
t_point	get_tile(t_point global_position, t_map *map)
{
	t_point	tile;

	tile = point_divide(global_position, TILE_SIZE);
	tile = point_add(tile, (t_point){((double)(global_position.x - tile.x * \
	TILE_SIZE) > TILE_SIZE * 0.5), ((double)(global_position.y - tile.y * \
	TILE_SIZE) > TILE_SIZE * 0.5)});
	if (tile.x >= (int) map->width || tile.y >= (int) map->width)
		return (point2(-1, -1));
	return (tile);
}
