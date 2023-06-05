/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/06 01:08:09 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../macro_headers/general_settings.h"
#include "../graphics_logic/graphics.h"

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

t_list	*get_actor_list(t_map *map, t_point pos, t_point area_size);

static inline	bool	is_closer(t_list *node, t_point position)
{
	return(point_len(point_subtract \
	(((t_actor *)node->content)->position, position))
	> point_len(point_subtract \
	(((t_actor *)node->next->content)->position, position)));
}

t_list	*sort_collision_list(t_list *lst, t_point position)
{
	t_list			*temp;
	unsigned int	len;
	unsigned int	j;
	unsigned int	i;

	len = ft_lstlen(lst);
	i = 0;
	while (i < len)
	{
		if (is_closer(lst, position))
			lst = ft_lst_swap_next(lst);
		temp = lst;
		j = 1;
		while (j < len - i - 1)
		{
			if (!is_closer(temp->next, position))
				temp->next = ft_lst_swap_next(temp->next);
			temp = temp->next;
			j++;
		}
		i++;
	}
	return (lst);
}

t_list	*get_collision_list(t_point position, t_point size, t_map *map)
{
	t_list	*head;
	t_point	area_size;

	head = NULL;
	position = point_add(position, point2(-1, -1));
	size = point_add(size, point2(2, 2));
	area_size = point_add(position, size);
	position.x = ft_max(position.x, 0);
	position.y = ft_max(position.y, 0);
	area_size.x = ft_min((int) area_size.x, (int)map->width);
	area_size.y = ft_min((int) area_size.y, (int)map->height);
	head = get_actor_list(map, position, area_size);
	if (head && head->next)
		head = sort_collision_list(head, position);
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

double	solve_collision_x(t_actor *actor1, double vel, t_actor *actor2)
{
	double	displacement;
	int		pos_after_movement;

	pos_after_movement = actor1->position.x + (int)vel;
	displacement = 0;
	
	if (vel > 0 && actor1->position.x < actor2->position.x)
		displacement = -1 * (pos_after_movement + actor1->size.x - actor2->position.x);
	else if (vel < 0 && actor1->position.x > actor2->position.x)
		displacement = actor2->position.x + actor2->size.x - pos_after_movement;
	return ((double)((int)vel) + (double)displacement);
}

double	solve_collision_y(t_actor *actor1, double vel, t_actor *actor2)
{
	int		displacement;
	int		pos_after_movement;
	int		old_vel;

	old_vel = vel;
	pos_after_movement = actor1->position.y + (int)vel;
	displacement = 0;
	
	if (vel > 0 && actor1->position.y < actor2->position.y)
		displacement = -1 * (pos_after_movement + actor1->size.y - actor2->position.y);
	else if (vel < 0 && actor1->position.y > actor2->position.y)
		displacement = actor2->position.y + actor2->size.y - pos_after_movement;
	return ((double)ft_abs_clamp((((int)vel) + displacement), 0, old_vel));
}

t_vector	solve_collision(t_actor *actor1, t_vector vel, t_actor *actor2)
{
	if (vel.y && !is_colliding(actor1, vector2(vel.x, 0), actor2))
		vel.y = solve_collision_y(actor1, vel.y, actor2);
	else if (vel.x && !is_colliding(actor1, vector2(0, vel.y), actor2))
		vel.x = solve_collision_x(actor1, vel.x, actor2);
	else
	{
		vel.y = solve_collision_y(actor1, vel.y, actor2);
		vel.x = solve_collision_x(actor1, vel.x, actor2);
	}
			// 	velocity.x = solve_collision_x(actor, velocity.x, (t_actor *)entity_list->content);
	// t_vector	displacement;
	// t_point		pos_after_movement;

	// pos_after_movement = point_add(actor1->position, vector_to_point(vel));
	// displacement = vector2(0 , 0);
	
	// if (vel.x > 0 && actor1->position.x < actor2->position.x)
	// 	displacement.x = -1 * (pos_after_movement.x + actor1->size.x - actor2->position.x);
	// else if (vel.x < 0 && actor1->position.x > actor2->position.x)
	// 	displacement.x = actor2->position.x + actor2->size.x - pos_after_movement.x;

	// if (vel.y > 0 && actor1->position.y < actor2->position.y)
	// 	displacement.y = -1 * (pos_after_movement.y + actor1->size.y - actor2->position.y);
	// else if (vel.y < 0 && actor1->position.y > actor2->position.y)
	// 	displacement.y = actor2->position.y + actor2->size.y - pos_after_movement.y;
	// vel.x = solve_collision_x(actor1, vel.x, actor2);
	// vel.y = solve_collision_y(actor1, vel.y, actor2);
	return (vel);
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
			velocity = solve_collision (actor, velocity, (t_actor *)entity_list->content);
			// actor->sprites = put_solid_color(actor->sprites, 0x00FF0000);
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
}
