/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actor_lists.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:49:02 by federico          #+#    #+#             */
/*   Updated: 2023/05/19 05:03:18 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_load_internal.h"
#include "../../so_long.h" //need to remove after creating actor header

// void	*enemy_init(t_point	position, char *filepath)
// {
// 	t_actor	*enemy;
// 	t_enemy	*enemy_characteristics;

// 	enemy = ft_calloc(1, sizeof(*enemy));
// 	if (!enemy)
// 		return (NULL);
// 	enemy_characteristics = ft_calloc(1, sizeof(*enemy_characteristics));
// 	if (!enemy_characteristics)
// 	{
// 		free(enemy);
// 		return (NULL);
// 	}
// 	enemy_characteristics->type = Default; //these are placeholders
// 	enemy->additional_struct = (void *)enemy_characteristics;
// 	enemy->height = TILE_SIZE; //i will need to implement a system to look the specifics up
// 	enemy->width = TILE_SIZE; //i'm thinking about using a second file to store additional info matching each element using their location
// 	(void)filepath; //temporarily unused, i will use it to find the "style sheet, it's going to be same name, diffrent extension"
// 	enemy->velocity = point2(0, 0);
// 	enemy->position = position;
// 	enemy->type = Enemy;
// 	return ((void *)enemy);
// }

void	enemy_free(void *enemy)
{
	t_actor	*en;

	en = (t_actor *)enemy;
	if (!enemy)
		return ;
	if (en->additional_struct)
		free(en->additional_struct);
	free(en);
}

// t_actor	*collectable_init(t_point position, char *filepath)
// {
// 	t_actor	*collectable;

// 	collectable = ft_calloc(1, sizeof(*collectable));
// 	if (!collectable)
// 		return (NULL);
// 	collectable->additional_struct = NULL;
// 	collectable->height = TILE_SIZE; 
// 	collectable->width = TILE_SIZE;
// 	(void)filepath; 
// 	collectable->position = position;
// 	collectable->type = Collectable;
// 	return ((void *)collectable);
// }

void	*enemy_additional(t_point position, char *filepath, t_actor *main)
{
	t_enemy	*enemy_characteristics;

	enemy_characteristics = ft_calloc(1, sizeof(*enemy_characteristics));
	if (!enemy_characteristics)
		return (NULL);
	enemy_characteristics->type = Default;//i gotta change this time
	(void)position;
	(void)filepath;
	(void)main;
	return (enemy_characteristics);
}

void	*collectable_additional(t_point	position, char *filepath, t_actor *main)
{
	(void)position;
	(void)filepath;
	(void)main;
	return (NULL);
}

void	*wall_additional(t_point position, char *filepath, t_actor *main)
{
	(void)position;
	(void)filepath;
	(void)main;
	return (NULL);
}

void	*player_additional(t_point position, char *filepath, t_actor *main)
{
	(void)position;
	(void)filepath;
	(void)main;
	return (NULL);
}

void	*exit_additional(t_point position, char *filepath, t_actor *main)
{
	bool	*open;

	open = ft_calloc(1, sizeof(bool *));
	(void)position;
	(void)filepath;
	(void)main;
	return (open);
}

t_actor	*actor_init(t_point	position, char *filepath, char type)
{
	t_actor	*actor;
	void	*(*additional)(t_point, char *, t_actor *);

	if (type == Wall)
		additional = wall_additional;
	else if (type == Enemy)
		additional = enemy_additional;
	else if (type == Collectable)
		additional = collectable_additional;
	else if (type == Player)
		additional = player_additional;
	else if (type == Exit)
		additional = exit_additional;
	else
		return (NULL);
	actor = ft_calloc(1, sizeof(*actor));
	if (!actor)
		return (NULL);
	actor->position = point_multiply(position, TILE_SIZE);
	actor->size = point2(TILE_SIZE, TILE_SIZE);
	actor->type = type;
	actor->additional_struct = additional(position, filepath, actor); //actor is passed to potentially edit some type specific characteristics
	return (actor);
}

int	map_list_append(t_map *map, char tile, t_point position)
{
	t_list	*new_node;
	t_list	**list_head;
	void	*content;

	//i may need to add support for more types of object/actor
	//for example interactable blocks/switches
	list_head = NULL;
	content = actor_init(position, map->map_path, tile);
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
