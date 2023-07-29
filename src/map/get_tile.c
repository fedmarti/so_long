/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:34:05 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/29 01:10:50 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_struct.h"
#include "../macro_headers/general_settings.h"



static inline t_point	get_valid_tile(t_point tile, t_point map_size)
{
	t_point	overflow;
	double	incline;

	if (tile.y == 0)
		return ((t_point){map_size.x, 0});
	else
		incline = (double) tile.x / (double) tile.y;
	overflow = get_overlow(tile, map_size);

	if (abs(overflow.x) >= abs(overflow.y))
	{
		tile.x += overflow.x;
		tile.y *= ft_abs_d(incline) + ((double) tile.y * ft_abs_d(incline) >= 0.5);	
	}
	else
	{
		
	}
}

//returns map coordinates from global coordinates
t_point	get_tile(t_point global_position, t_map *map)
{
	t_point	tile;
	// t_point	clamped_tile;

	tile = point_divide(global_position, TILE_SIZE);
	tile = point_add(tile, (t_point){((double)(global_position.x - tile.x * \
	TILE_SIZE) > TILE_SIZE * 0.5), ((double)(global_position.y - tile.y * \
	TILE_SIZE) > TILE_SIZE * 0.5)});
		// clamped_tile = (t_point){ft_clamp(tile.x, 0, (int) map->width),}
	return (tile);
	// return (get_valid_tile(tile, (t_point){(int)map->width, (int)map->height}));
}
