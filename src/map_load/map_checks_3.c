/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:19:39 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:24:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../map/map_struct.h"
#include "../actor_logic/actor_structs.h"

bool	is_in_map(t_point tile, t_point map_size)
{
	return ((tile.x >= 0 && tile.x < map_size.x) \
			&& (tile.y >= 0 && tile.y < map_size.y));
}

//for the type of objects that need to be unique (player, exit...)
//returns 1 if they have already been found
//returns 0 and adds their address to the map struct if not
int	check_uniqueness(t_map *map, char tile, t_point point)
{
	t_actor	**actor;

	if (tile == Player)
		actor = &map->player;
	else
		actor = &map->exit;
	if (*actor)
		return (1);
	*actor = map->tiles[point.y][point.x].entity_list->content;
	return (0);
}

int		map_list_append(t_map *map, char tile, t_point position);

int	check_tile(t_map *map, char tile, t_point point)
{
	if (is_in_map(point, point2(map->width, map->height)))
		map->tiles[point.y][point.x].coordinates = point;
	if (tile != Empty && tile != Void)
	{
		if (map_list_append(map, tile, point))
			return (1);
	}
	if (tile == Player || tile == Exit)
	{
		if (check_uniqueness(map, tile, point))
			return (1);
	}
	return (0);
}
