/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_on_ground.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 00:31:34 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/28 00:38:09 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "../actor_logic/actor_structs.h"
#include "../2d_geometry/rectangle.h"
#include "../map/map.h"

bool	is_list_aabb(t_actor *actor, t_rectangle hitbox, t_list *list)
{
	t_actor	*temp_actor;

	while (list)
	{
		temp_actor = list->content;
		if (temp_actor != actor && AABB_rectangles(hitbox, \
		(t_rectangle){temp_actor->position, temp_actor->size}))
			return (true);
		list = list->next;
	}
	return (false);
}

bool	is_on_ground(t_actor *actor, t_map *map)
{
	t_rectangle	feet_hitbox;
	t_list		*entity_list;
	t_point		actor_tile;
	t_point		tile_area;
	t_point		i;

	feet_hitbox.pos = \
	(t_point){actor->position.x, actor->position.y + actor->size.y};
	feet_hitbox.size = (t_point){actor->size.x, 1};
	actor_tile = get_tile(actor->position, map);
	i.y = actor_tile.y;
	tile_area = point_add(actor_tile, (t_point){1, 1});
	while (i.y <= tile_area.y)
	{
		i.x = actor_tile.x - 1;
		while (i.x <= tile_area.x)
		{
			entity_list = map->tiles[i.y][i.x].entity_list;
			if (is_list_aabb(actor, feet_hitbox, entity_list))
				return (true);
			i.x++;
		}
		i.y++;
	}
	return (false);
}
