/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actor_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:23:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 18:24:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "actor_structs.h"
#include "../graphics_logic/graphics.h"
#include "../map/map.h"
#include <stdlib.h>

// void	actor_free(t_actor	**actor)
// {
// 	if (!*actor)
// 		return ;
// 	if ((*actor)->additional_struct)
// 		free((*actor)->additional_struct);
// 	free(*actor);
// 	*actor = NULL;
// }

static void	free_from_map(t_actor *actor, t_map *map)
{
	t_point	tile;
	t_list	*temp;

	temp = NULL;
	if (!actor || !map)
		return ;
	if (actor->type == Collectable)
		temp = ft_lstpop_one(actor, &map->collectable_list);
	else if (actor->type == Enemy)
		temp = ft_lstpop_one(actor, &map->enemy_list);
	else if (actor->type == Player)
		map->player = NULL;
	else if (actor->type == Exit)
		map->exit = NULL;
	if (temp)
		free(temp);
	temp = NULL;
	tile = get_tile(actor->position, map);
	if (map->tiles && tile.x >= 0 && tile.x < (int) map->width \
	&& tile.y >= 0 && tile.y < (int) map->height)
		temp = ft_lstpop_one(actor, &map->tiles[tile.y][tile.x].entity_list);
	if (temp)
		free(temp);
}

void	actor_free(t_actor *actor, t_map *map, void *mlx)
{
	free_from_map(actor, map);
	if (actor->sprite)
		img_free(actor->sprite, mlx);
	free(actor);
}