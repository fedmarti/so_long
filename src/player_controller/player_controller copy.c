/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller copy.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/30 00:53:27 by fedmarti         ###   ########.fr       */
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

typedef	struct s_data_pack
{
	t_point		area_size;
	t_actor		*actor;
	t_vector	*vel;
	t_point		last_gba;
};

void	ft_swap_i(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_list	*check_more_tiles(t_point tile, struct s_data_pack *data, t_map *map)
{
	t_point	i;
	t_list	*entity_list;
	t_point	target;
	t_point	p_sign;

	i = (t_point){-(data->last_gba.x != 0), -(data->last_gba.y != 0)};
	target = (t_point){data->area_size.x - 1, data->area_size.y - 1};
	target = (t_point){target.x * -i.x, target.y * -i.y};
	if (data->last_gba.x < 0)
		ft_swap_i(&i.x, &target.x);
	if (data->last_gba.y < 0)
		ft_swap_i(&i.y, &target.y);
	p_sign = (t_point){sign(target.x - i.x), sign(target.y - i.y)};
	while (i.x != target.x)
	{
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
		i.x++;
	}
	get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
	data->actor, *data->vel, &entity_list);
	while (i.y++ != target.y)
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
	return (entity_list);
}

static t_point	vars_init(struct s_data_pack *data, t_point *i, t_point tile)
{
	data->area_size = point_divide(data->actor->size, TILE_SIZE);
	data->area_size = (t_point){!data->area_size.x + data->area_size.x, \
	!data->area_size.y + data->area_size.y};
	i->y = tile.y - (data->area_size.y >> 1) - (data->area_size.y & 1);
	i->y += (abs(i->y) * i->y < 0);
	data->area_size = point_add(data->area_size, (t_point){2, 2});
	return (point_add(*i, data->area_size));
}

t_list	*check_surrounding_area(t_point tile, struct s_data_pack *data, t_map *map)
{
	t_list		*entity_list;
	t_point		tile_area;
	t_point		i;

	entity_list = NULL;
	tile_area = vars_init(data, &i, tile);
	while (i.y <= tile_area.y && i.y < (int) map->height)
	{
		i.x = tile.x - (data->area_size.x >> 1) - (data->area_size.x & 1);
		i.x += (abs(i.x) * i.x < 0);
		while (i.x <= tile_area.x && i.x < (int) map->width)
		{
			get_s_aabbs(map->tiles[i.y][i.x].entity_list, data->actor, \
			*data->vel, &entity_list);
			i.x++;
		}
		i.y++;
	}
	return (entity_list);
}

#include "../2d_geometry/gba_line_draw.h"

t_vector	solve_s_aabbs(struct s_data_pack *data, t_list *collision_list)
{
	
}

//uses the generalized bresemham algorithm to select a line of map tiles
//to check, starting from the current tile, 
//in the direction of the velocity vector
void \
	check_collisions_gba(t_line mov, struct s_data_pack data, t_map *map)
{
	t_list		*collision_list;
	t_point		i;
	t_gba_data	gba;

	gba = gba_init(mov.p1, mov.p2);
	i = mov.p1;
	collision_list = check_surrounding_area(mov.p1, &data, map);
	data.last_gba = gba_next(&gba, &i);
	while ((data.last_gba.x || data.last_gba.y) || collision_list)
	{
		if (collision_list)
		{
			*data.vel = solve_s_aabbs(&data, collision_list); 
		}
		//solve aabbs
		//if trajectory changed -> return 
		//if there's still velocity left check again
		data.last_gba = gba_next(&gba, &i);
		ft_lstadd_back(&collision_list, check_more_tiles(i, &data, map));
		
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
	colliding_actors = check_collisions_gba(line_in_area(i, target_tile, (t_point){(int)map->width, (int)map->height}), (struct s_data_pack){(t_point){0, 0}, actor, &velocity}, map);
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
