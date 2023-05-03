/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actor_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:49:02 by federico          #+#    #+#             */
/*   Updated: 2023/05/03 19:40:34 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load.h"

void	*enemy_init(t_point	position, char *filepath)
{
	t_actor	*enemy;
	t_enemy	*enemy_characteristics;

	enemy = malloc(sizeof(*enemy));
	if (!enemy)
		return (NULL);
	enemy_characteristics = malloc(sizeof(*enemy_characteristics));
	if (!enemy_characteristics)
	{
		free(enemy);
		return (NULL);
	}
	enemy_characteristics->type = Default; //these are placeholders
	enemy->additional_stuct = (void *)enemy_characteristics;
	enemy->height = 16; //i will need to implement a system to look the specifics up
	enemy->width = 16; //i'm thinking about using a second file to store additional info matching each element using their location
	(void)filepath; //temporarily unused, i will use it to find the "style sheet, it's going to be same name, diffrent extension"
	enemy->velocity = vector2(0, 0);
	enemy->position = position;
	return ((void *)enemy);
}

void	enemy_free(void *enemy)
{
	t_actor	*en;

	en = (t_actor *)enemy;
	if (!enemy)
		return ;
	if (en->additional_stuct)
		free(en->additional_stuct);
	free(en);
}

int	map_list_append(t_map *map, char tile, t_point position)
{
	t_list	*new_node;
	t_list	**list_head;
	void	*content;

	//i may need to add support for more types of object/actor
	//for example interactable blocks/switches 
	content = NULL;
	if (tile == Enemy)
	{
		content = enemy_init(position, map->map_path);
		list_head = &map->enemy_list;
	}
	else if (tile == Collectable)
	{
		content = (void *)vector2_pointer(position);
		list_head = &map->collectable_list;
	}
	if (!content)
		return (1);
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		free(content);
		return (1);
	}
	ft_lstadd_back(list_head, new_node);
	return (0);
}
