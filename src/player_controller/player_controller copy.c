/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller copy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/28 04:40:18 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../macro_headers/general_settings.h"
#include "../graphics_logic/graphics.h"
#include "../2d_geometry/rectangle.h"
#include "swept_aabb.h"

t_vector	get_player_direction(t_input input)
{
	t_vector	direction;

	direction = vector2(input.right - input.left, 0 * input.down - input.up);
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
	size = (t_point){size.x + !size.x, size.y + !size.y};
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



//only works with squares so far
// AABB collision

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
	t_list			*collision_list;

	i = 0;
	collision_list = NULL;
	while (entity_list)
	{
		hit = shoot_ray_to_entity(actor, vel, entity_list->content);
		if (hit.collision && is_colliding(actor, vel, (t_actor *)entity_list->\
				content))
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

#include "../map/map.h"
#include "../2d_geometry/line.h"


bool	is_in_lst(t_list **list, t_swept_aabb collision)
{
	t_list			*node;
	t_swept_aabb	*temp;

	node = *list;
	while (node)
	{
		temp = node->content;
		if (temp->target == collision.target)
			return (true);
		node = node->next;
	}
	return (false);
}

void	get_s_aabbs(t_list *tile_list, t_actor *actor, t_vector vel, t_list **entity_list)
{
	t_swept_aabb	result;
	t_swept_aabb	*content;
	t_list			*new_node;

	while (tile_list)
	{
		result = swept_aabb(actor, vel, tile_list->content);
		if (result.collision && !is_in_lst(entity_list, result))
		{
			content = malloc(sizeof(*content));
			if (!content)
				break ;
			*content = result;
			new_node = ft_lstnew(content);
			if (!new_node)
			{
				free(content);
				break ;
			}
			ft_lstadd_back(entity_list, content);
		}
		tile_list = tile_list->next;
	}
}

t_list *check_surrounding_area(t_point tile, t_actor *actor, t_vector vel, t_map *map)
{
	t_list		*entity_list;
	t_point		a_size;
	t_point		tile_area;
	t_point		i;

	entity_list = NULL;
	a_size = point_divide(actor->size, TILE_SIZE);
	a_size = (t_point){!a_size.x + a_size.x, !a_size.y + a_size.y};
	i.y = tile.y - (a_size.y >> 1) - (a_size.y & 1);
	i.y += (abs(i.y) * i.y < 0);
	tile_area = (t_point){tile.x + (a_size.x >> 1) + (a_size.x & 1), \
	tile.y + (a_size.y >> 1) + (a_size.y & 1)};
	while (i.y <= tile_area.y)
	{
		i.x = tile.y - (a_size.x >> 1) - (a_size.x & 1);
		i.x += (abs(i.x) * i.x < 0);
		while (i.x <= tile_area.x)
		{
			get_s_aabbs(map->tiles[i.y][i.x].entity_list, actor, vel, \
			&entity_list);
			i.x++;
		}
		i.y++;
	}
	return (entity_list);
}

static inline t_point init_vars(t_point delta, t_point *sign, int *e, int *ex_change)
{
	*sign = point2(ft_sign(delta.x), ft_sign(delta.y));
	*ex_change = (ft_abs(delta.y) > ft_abs(delta.x));
	delta = (t_point){abs_max_signed(delta.x, delta.y), \
	abs_min_signed(delta.x, delta.y)};
	*e = 2 * ft_abs(delta.y) - ft_abs(delta.x);
	return (delta);
}

void \
	check_collisions_gba(t_line mov, t_actor *actor, t_vector vel, t_map *map)
{
	t_list	*collision_list;
	t_point	delta;
	t_point	sign;
	int		ex_change;
	int		e;

	collision_list = NULL;
	delta = init_vars(point_subtract(mov.p2, mov.p1), &sign, &e, &ex_change);
	while (point_cmpr(mov.p1, mov.p2))
	{
		ft_lstadd_back(&collision_list, check_surrounding_area(mov.p1, actor, vel, map));
		//solve aabbs
		//if trajectory changed -> return 
		//if there's still velocity left check again
		while (e >= 0)
		{
			mov.p1 = \
			point_add(point2(ex_change * sign.x, !ex_change * sign.y), mov.p1);
			e -= ft_abs(2 * delta.x);
		}
		mov.p1 = \
		point_add(point2(!ex_change * sign.x, ex_change * sign.y), mov.p1);
		e += ft_abs(2 * delta.y);
	}
}

void	move_and_collide(t_actor *actor, t_vector velocity, t_map *map)
{
	t_list	*temp;
	t_list	*colliding_actors;
	t_point	i;
	t_point	movemet_target;
	t_point	target_tile;

	i = get_tile(actor->position, map);
	movemet_target = point_add(actor->position, vector_to_point(velocity));
	target_tile = get_tile(movemet_target, map);
	if (!point_cmpr(i, target_tile))
		colliding_actors = check_surrounding_area(target_tile, actor, velocity, map);
	while (colliding_actors)
	{
		temp = colliding_actors;
		if (is_colliding(actor, velocity, (t_actor *)temp->content))
			velocity = solve_collision (actor, velocity, \
			(t_actor *)temp->content);
		colliding_actors = temp->next;
		ft_lstdelone(temp, ft_do_nothing);
		// actor->sprite = put_solid_color(actor->sprite, 0x00FF0000);
	}
	actor->position = point_add(actor->position, vector_to_point(velocity));
	actor->velocity = velocity;
}

void	player_controller(t_data *data)
{
	t_vector	direction;
	t_vector	velocity;

	direction = get_player_direction(data->input);
	velocity = vector_multiply(direction, (PLAYER_SPEED + (DASH_BOOST * data->input.shift_left)));
	velocity = vector_multiply(velocity, ((double)data->time.delta / ONE_SEC));
	velocity.y += data->map->player->velocity.y;
	if (data->input.space && is_on_ground(data->map->player, data->map))
		velocity.y = -JUMP;
	//change system to take entity list, base it on the bres_line_draw
	move_and_collide(data->map->player, velocity, data->map);
	/*implement update tilemap position*/
	
}
