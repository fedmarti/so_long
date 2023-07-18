/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 19:22:03 by fedmarti         ###   ########.fr       */
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
		direction = vector_multiply(direction, 0.70710678118);
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
	tile = point_add(tile, (t_point){((double)(global_position.x - tile.x * \
	TILE_SIZE) > TILE_SIZE * 0.5), ((double)(global_position.y - tile.y * \
	TILE_SIZE) > TILE_SIZE * 0.5)});
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
	double	old_vel;

	old_vel = vel;
	pos_after_movement = actor1->position.x + (int)vel;
	displacement = 0;
	if (vel > 0 && actor1->position.x < actor2->position.x)
		displacement = -1 * (pos_after_movement + actor1->size.x - actor2->position.x);
	else if (vel < 0 && actor1->position.x > actor2->position.x)
		displacement = actor2->position.x + actor2->size.x - pos_after_movement;
	return ((double)ft_abs_clamp_d((vel + (double)displacement), 0, old_vel));
	// return (vel + displacement);
}

double	solve_collision_y(t_actor *actor1, double vel, t_actor *actor2)
{
	int		displacement;
	int		pos_after_movement;
	double	old_vel;

	old_vel = vel;
	pos_after_movement = actor1->position.y + (int)vel;
	displacement = 0;
	if (vel > 0 && actor1->position.y < actor2->position.y)
		displacement = -1 * (pos_after_movement + actor1->size.y - actor2->position.y);
	else if (vel < 0 && actor1->position.y > actor2->position.y)
		displacement = actor2->position.y + actor2->size.y - pos_after_movement;
	return ((double)ft_abs_clamp_d((vel + (double)displacement), 0, old_vel));
	// return (vel + displacement);
}

t_vector	solve_collision(t_actor *actor1, t_vector vel, t_actor *actor2)
{
	t_vector	displacement;
	t_point		new_pos;

	new_pos = point_add(actor1->position, vector_to_point(vel));
	displacement = (t_vector){0,0};
	if (vel.x < 0 && actor1->position.x >= actor2->position.x)
		displacement.x = actor2->position.x + actor2->size.x - new_pos.x;
	else if (vel.x > 0 && actor1->position.x <= actor2->position.x)
		displacement.x = -1 * (new_pos.x + actor1->size.x - actor2->position.x);
	if (vel.y < 0 && actor1->position.y >= actor2->position.y)
		displacement.y = actor2->position.y + actor2->size.y - new_pos.y;
	else if (vel.y > 0 && actor1->position.y <= actor2->position.y)
		displacement.y = -1 * (new_pos.y + actor1->size.y - actor2->position.y);
	if (ft_abs_d(displacement.x) > ft_abs_d(vel.x))
		displacement.x = 0;
	else if (ft_abs_d(displacement.y) > ft_abs_d(vel.y))
		displacement.y = 0;
	// if (vel.y && !is_colliding(actor1, vector2(vel.x, 0), actor2))
	// 	vel.y = solve_collision_y(actor1, vel.y, actor2);
	// else if (vel.x && !is_colliding(actor1, vector2(0, vel.y), actor2))
	// 	vel.x = solve_collision_x(actor1, vel.x, actor2);
	// else
	// {
	// 	vel.y = solve_collision_y(actor1, vel.y, actor2);
	// 	vel.x = solve_collision_x(actor1, vel.x, actor2);
	// }
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
	return (vector_add(displacement, vel));
}

t_vector	update_sub_pixels(t_vector	sub_pix_pos, t_vector velocity)
{
	t_vector	sub_pixels;

	sub_pixels = vector_subtract \
	(velocity, vector2((double)((int)velocity.x), (double)((int)velocity.y)));
	sub_pix_pos = vector_add(sub_pix_pos, sub_pixels);
	return (sub_pix_pos);
}

t_vector	recover_sub_pixels(t_vector	*sub_pixels, t_vector vel)
{
	if (ft_abs_d(sub_pixels->x) >= 1)
	{
		vel.x += (int)sub_pixels->x;
		sub_pixels->x -= (int)sub_pixels->x;
	}
	if (ft_abs_d(sub_pixels->y) >= 1)
	{
		vel.y += (int)sub_pixels->y;
		sub_pixels->y -= (int)sub_pixels->y;
	}
	return (vel);
}

#include "../2d_geometry/raycast.h"


void	get_starting_points(t_point *sp, t_point dir, t_actor *actor)
{
	sp[0] = actor->position;
	sp[1] = point_add(actor->position, point_multiply(actor->size, 0.5));
	sp[2] = point_add(actor->position, actor->size);
	sp[1].x += actor->size.x * 0.5 * ft_sign(dir.x);
	sp[1].y += actor->size.y * 0.5 * ft_sign(dir.y);
	if (ft_sign(dir.x) == ft_sign(dir.y))
	{
		sp[0].y += actor->size.y;
		sp[2].y -= actor->size.y;
	}
	if (!dir.x && dir.y)
		sp[2 * (dir.y < 0)].y += actor->size.y * ft_sign(dir.y);
	else if (!dir.y && dir.x)
		sp[2 * (dir.x < 0)].x += actor->size.x * ft_sign(dir.x);
}

t_hit	rec_shoot_rays(t_actor *actor, t_point direction_vector, t_actor *target)
{
	t_hit	hit;
	t_hit	temp_hit;
	t_point	starting_point[3];
	
	get_starting_points(starting_point, direction_vector, actor);
	hit = raycast_to_rectangle(starting_point[0], point_add(starting_point[0],\
	direction_vector), target->position, target->size);
	temp_hit = raycast_to_rectangle(starting_point[1], point_add\
	(starting_point[1], direction_vector), target->position, target->size);
	if (is_h2_closer(hit, temp_hit))
		hit = temp_hit;
	temp_hit = raycast_to_rectangle(starting_point[2], point_add\
	(starting_point[2], direction_vector), target->position, target->size);
	if (is_h2_closer(hit, temp_hit))
		hit = temp_hit;
	return (hit);
}

t_actor	*get_colliding_actor(t_list *entity_list, t_actor *actor, t_vector vel)
{
	t_list	*temp_node;
	t_hit	hit;
	t_hit	temp_hit;
	t_actor	*ca;
	t_actor	*temp_actor;

	ca = NULL;
	temp_actor = NULL;
	hit = (t_hit){(t_point){0,0}, (t_point){0,0}, false};
	while (entity_list)
	{
		temp_actor = entity_list->content;
		temp_hit = rec_shoot_rays(actor, vector_to_point(vel), (t_actor *)entity_list->content);
		if (is_h2_closer(hit, temp_hit))
		{
			ca = temp_actor;
			hit = temp_hit;
		}
		temp_node = entity_list->next;
		ft_lstdelone(entity_list, ft_do_nothing);
		entity_list = temp_node;
	}
	return (ca);
}

// void	move_and_collide(t_actor *actor, t_vector velocity, t_list *entity_list)
// {
// 	t_list			*colliding_actors;
// 	t_list			*temp_node;
// 	t_rectangle		*temp_rec;

// 	colliding_actors = get_colliding_actors(entity_list, actor, velocity);
// 	while (colliding_actors)
// 	{
// 		temp_rec = (t_rectangle *)colliding_actors->content;
// 		draw_ray_and_rec(*actor, vector_to_point(velocity), temp_rec, data);
// 		if (is_colliding(actor, velocity, temp_rec))
// 		{
// 			velocity = solve_collision (actor, velocity, temp_rec);
// 			color = 0x30ff0000;
// 		}
// 		temp_node = colliding_actors;
// 		colliding_actors = colliding_actors->next;
// 		ft_lstdelone(temp_node, ft_do_nothing);
// 	}
// 	actor->position = point_add(actor->position, vector_to_point(velocity));
// 	// ft_lstclear(&entity_list, ft_do_nothing);
// }

t_hit	shoot_ray_to_entity(t_actor *actor, t_vector vel, t_actor *entity)
{
	return (rec_shoot_ray((t_rectangle){actor->position, actor->size}, \
	vector_to_point(vel), (t_rectangle){entity->position, entity->size}));
}

// void	add_to_collision_list(t_list **list, t_actor *actor, unsigned short )

void	add_to_collision_list(t_list **collision_list, t_actor *actor, unsigned short *hit_dist, unsigned short arr_len)
{
	unsigned short	list_position;
	// unsigned short	i;
	unsigned short	current_hit_dist;
	t_list			*new_node;

	list_position = 0;
	// i = 0;
	current_hit_dist = hit_dist[arr_len - 1];
	while (arr_len--)
	{
		if (*hit_dist < current_hit_dist)
			list_position++;
		hit_dist++;
		// i++;
	}
	new_node = ft_lstnew(actor);
	if (!new_node)
		return ;
	ft_lst_insert_n(collision_list, new_node, list_position);
}

#ifndef MAX_COLLISIONS
# define MAX_COLLISIONS 5U
#endif

unsigned short	max_collision_chk(unsigned short *arr, unsigned short i, unsigned short val)
{
	unsigned short	j;
	unsigned short	index_of_highest;

	if (i < MAX_COLLISIONS)
		return (val);
	j = 0;
	index_of_highest = MAX_COLLISIONS - 1;
	while (j < MAX_COLLISIONS)
	{
		if (arr[index_of_highest] < arr[j])
			index_of_highest = j;
		j++;
	}
	if (val > arr[index_of_highest])
		return (arr[MAX_COLLISIONS - 1]);
	j = index_of_highest;
	while (j < MAX_COLLISIONS - 1)
	{
		arr[j] = arr[j + 1];
		j++;
	}
	return (val);
}

void ft_lst_remove_n(t_list **list, int n, void (*del)(void *))
{
	t_list	*temp;
	t_list	*prev;

	if (!*list)
		return ;
	temp = *list;
	prev = NULL;
	while (n-- && temp->next)
	{
		prev = temp;
		temp = temp->next;
	}
	if (!prev)
		*list = temp->next;
	else
		prev->next = temp->next;
	ft_lstdelone(temp, del);
}

unsigned short	arr_max_us(unsigned short *arr, unsigned short len)
{
	unsigned short	i;
	unsigned short	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (arr[j] < arr[i])
			j = i;
		i++;
	}
	return (j);
}

void arr_rm_us(unsigned short *arr, unsigned short i, unsigned short len)
{
	while (i < len)
	{
		arr[i] = arr[i + 1];
		i++;
	}
}

bool	max_collision_check(unsigned short *arr, t_list **list, \
unsigned short val, unsigned short *i)
{
	unsigned short index_of_highest;

	if (*i == MAX_COLLISIONS)
	{
		index_of_highest = arr_max_us(arr, MAX_COLLISIONS);
		if (val > arr[index_of_highest])
			return (false);
		ft_lst_remove_n(list, MAX_COLLISIONS, ft_do_nothing);
		arr_rm_us(arr, index_of_highest, MAX_COLLISIONS);
		*i -= 1;
	}
	arr[*i] = val;
	*i += 1;
	return (true);
}

t_list	*get_colliding_actors(t_list *entity_list, t_actor *actor, t_vector vel)
{
	t_list			*temp_node;
	unsigned short	hit_distance[MAX_COLLISIONS];
	unsigned short	i;
	struct s_hit	hit;
	t_list			*collision_list;

	i = 0;
	collision_list = NULL;
	while (entity_list)
	{
		hit = shoot_ray_to_entity(actor, vel, entity_list->content);
		if (hit.collision)
		{
			if (max_collision_check(hit_distance, &collision_list, (unsigned \
			short) line_len((t_line){hit.origin, hit.intersection}), &i))
				add_to_collision_list(&collision_list, (t_actor *)entity_list->\
				content, hit_distance, i);
		}
		temp_node = entity_list->next;
		ft_lstdelone(entity_list , ft_do_nothing);
		entity_list = temp_node;
	}
	return (collision_list);
}

void	move_and_collide(t_actor *actor, t_vector velocity, t_map *map)
{
	t_point	actor_size;
	t_list	*entity_list;
	t_list	*temp;
	t_list	*colliding_actors;

	actor_size = point_divide(actor->size, TILE_SIZE);
	entity_list = get_collision_list \
	(get_tile(actor->position, map), actor_size, map);
	velocity = recover_sub_pixels(&actor->sub_pixel_pos, velocity);
	// if (entity_list && entity_list->next)
	// 	entity_list = sort_collision_list(entity_list, point_add(actor->position, vector_to_point(velocity)));
	colliding_actors = get_colliding_actors(entity_list, actor, velocity);
	while (colliding_actors)
	{
		temp = colliding_actors;
		if (is_colliding(actor, velocity, (t_actor *)temp->content))
			velocity = solve_collision (actor, velocity, \
			(t_actor *)temp->content);
		colliding_actors = temp->next;
		ft_lstdelone(temp, ft_do_nothing);
		// actor->sprites = put_solid_color(actor->sprites, 0x00FF0000);
	}
	actor->sub_pixel_pos = update_sub_pixels(actor->sub_pixel_pos, velocity);
	actor->position = point_add(actor->position, vector_to_point(velocity));
}

void	player_controller(t_data *data)
{
	t_vector	direction;

	direction = get_player_direction(data->input);
	move_and_collide(data->map->player, vector_multiply(direction, (PLAYER_SPEED + (DASH_BOOST * data->input.shift_left))), data->map);
}
