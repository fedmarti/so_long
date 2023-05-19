/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/18 17:00:46 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../macro_headers/general_settings.h"

t_vector	get_player_direction(t_input input)
{
	t_vector	direction;

	direction = vector2(input.right - input.left, input.down - input.up);
	if (direction.x && direction.y)
		direction = vector_normalize(direction);
	return (direction);
}

bool	is_in_map(t_point tile, t_point map_size)
{
	return ((tile.x >= 0 && tile.x < map_size.x) \
			&& (tile.y >= 0 && tile.y < map_size.y));
}

// returns a copy of the list, DOES NOT copy the content 
// the new list points to the old content
t_list	*ft_lstcopy(t_list *head)
{
	t_list	*temp;
	t_list	*new;
	t_list	*new_list_head;

	temp = head;
	new_list_head = NULL;
	while (temp)
	{
		new = ft_lstnew(temp->content);
		if (!new)
		{
			ft_lstclear(&new_list_head, ft_do_nothing);
			return (NULL);
		}
		ft_lstadd_back(&new_list_head, new);
		temp = temp->next;
	}
	return (new_list_head);
}

t_list	*get_collision_list(t_point position, t_point size, t_map *map)
{
	t_list	*head;
	t_point	map_size;
	t_point	i;

	map_size = point2(map->width, map->height);
	if (position.x < 0 || position.y < 0)
		return (NULL);
	head = NULL;
	i.y = 0;
	position = point_add(position, point2(-1, -1));
	while (position.y + i.y < size.y + 1)
	{
		i.x = 0;
		while (position.x + i.x < size.x + 1)
		{
			if (is_in_map(point_add(position, i), map_size))
				head = ft_lstcopy(map->tiles[position.y + i.y][position.x + i.x].entity_list);
			i.x++;
		}
		i.y++;
	}
	return (head);
}

//returns map coordinates from global coordinates
t_point	get_tile(t_point global_position, t_map *map)
{
	t_point	tile;

	tile = point_divide(global_position, TILE_SIZE);
	if (tile.x >= (int) map->width || tile.y >= (int) map->width)
		return	(point2(-1,-1));
	return (tile);
}

//only works with squares so far
// AABB collision
bool	is_colliding(t_actor *actor1, t_vector vel, t_actor *actor2)
{
	t_point	pos_after_movement;


	// rect1.x < rect2.x + rect2.w &&
    // rect1.x + rect1.w > rect2.x &&
    // rect1.y < rect2.y + rect2.h &&
    // rect1.h + rect1.y > rect2.y
	if (actor1 == actor2)
		return (false);
	pos_after_movement = point_add(actor1->position, vector_to_point(vel));
	return (pos_after_movement.x < actor2->position.x + actor2->size.x
		&& pos_after_movement.x + actor1->size.x > actor2->position.x
		&& pos_after_movement.y < actor2->position.y + actor2->size.y
		&& pos_after_movement.y + actor1->size.y > actor2->position.y);
}

t_vector	solve_collision(t_actor *actor1, t_vector vel, t_actor *actor2)
{
	t_vector	displacement;
	t_point		pos_after_movement;

	pos_after_movement = point_add(actor1->position, vector_to_point(vel));
	displacement = point_to_vector \
	(point_subtract(pos_after_movement, actor2->position));	
	return (vector_add(vel, displacement));
}
void	move_and_collide(t_actor *actor, t_vector velocity, t_map *map)
{
	t_point	actor_size;
	t_list	*entity_list;
	t_list	*temp;

	actor_size = point_divide(actor->size, TILE_SIZE);
	entity_list = get_collision_list \
	(get_tile(actor->position, map), actor_size, map);
	while (entity_list)
	{
		if (is_colliding(actor, velocity, (t_actor *)entity_list->content))
		{
			velocity = solve_collision \
			(actor, velocity, (t_actor *)entity_list->content);
		}
		temp = entity_list->next;
		ft_lstdelone(entity_list, ft_do_nothing);
		entity_list = temp;
	}
	actor->position = point_add(actor->position, vector_to_point(velocity));
}

void	player_controller(t_data *data)
{
	t_vector	direction;

	direction = get_player_direction(data->input);
	move_and_collide(data->map->player, vector_multiply(direction, (PLAYER_SPEED + (DASH_BOOST * data->input.shift_left))), data->map);
	//HANDLE COLLISIONS
}