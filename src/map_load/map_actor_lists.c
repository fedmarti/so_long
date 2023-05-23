/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actor_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:49:02 by federico          #+#    #+#             */
/*   Updated: 2023/05/22 22:53:38 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load_internal.h"
#include "../../so_long.h" //need to remove after creating actor header
#include "../actor_logic/actor.h"

int	map_list_append(t_map *map, char tile, t_point position)
{
	t_list	*new_node;
	t_list	**list_head;
	void	*content;

	//i may need to add support for more types of object/actor
	//for example interactable blocks/switches
	list_head = NULL;
	content = actor_init(position, map->map_path, tile, map->data);
	if (tile == Enemy)
		list_head = &map->enemy_list;
	else if (tile == Collectable)
		list_head = &map->collectable_list;
	if (!content)
		return (1);
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		free(content);
		return (1);
	}
	if (list_head)
		ft_lstadd_back(list_head, new_node);
	ft_lstadd_back(&map->tiles[position.y][position.x].entity_list, new_node);
	return (0);
}
