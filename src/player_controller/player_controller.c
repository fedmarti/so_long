/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/30 05:10:53 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../macro_headers/general_settings.h"
#include "../graphics_logic/graphics.h"
#include "../2d_geometry/rectangle.h"
#include "swept_aabb.h"
#include <math.h>

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

static inline	bool	is_closer(t_list *node)
{
	return(((t_swept_aabb *)node->content)->collision_time) \
	> (((t_swept_aabb *)node->next->content)->collision_time);
}

t_list	*sort_collision_list(t_list *lst)
{
	t_list			*temp;
	unsigned int	len;
	unsigned int	j;
	unsigned int	i;

	len = ft_lstlen(lst);
	i = 0;
	while (i < len)
	{
		if (is_closer(lst))
			lst = ft_lst_swap_next(lst);
		temp = lst;
		j = 1;
		while (j < len - i - 1)
		{
			if (!is_closer(temp->next))
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
		head = sort_collision_list(head);
	return (head);
}




#ifndef MAX_COLLISIONS
# define MAX_COLLISIONS 5U
#endif



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

	// double	collision_time;
	// t_vector	normal;
	// bool		collision;
	// t_actor		*target;

void	get_s_aabbs(t_list *tile_list, t_actor *actor, t_vector vel, t_list **entity_list)
{
	t_swept_aabb	result;
	t_swept_aabb	*content;
	t_list			*new_node;
	
	while (tile_list)
	{
		result = (t_swept_aabb){0.0, (t_vector){0, 0}, false, NULL};
		if (actor != tile_list->content)
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
			ft_lstadd_back(entity_list, new_node);
		}
		tile_list = tile_list->next;
	}
}

struct s_data_pack
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

static inline int _add(int *a, int *b)
{
	*a += *b;
	return (1);
}

static inline void	_vars_init(t_point *target, struct s_data_pack *data, t_point *i, t_point tile)
{
	*i = (t_point){-(data->last_gba.x != 0), -(data->last_gba.y != 0)};
	*target = (t_point){data->area_size.x - 1, data->area_size.y - 1};
	*target = (t_point){target->x * -i->x, target->y * -i->y};
	i->x -= i->x * (tile.x == 0);
	i->y -= i->y * (tile.y == 0);
	if (data->last_gba.x < 0)
		ft_swap_i(&i->x, &target->x);
	if (data->last_gba.y < 0)
		ft_swap_i(&i->y, &target->y);
}

t_list	*check_more_tiles(t_point tile, struct s_data_pack *data, t_map *map)
{
	t_point	i;
	t_list	*entity_list;
	t_point	target;
	t_point	p_sign;

	_vars_init(&target, data, &i, tile);
	p_sign = (t_point){ft_sign(target.x - i.x), ft_sign(target.y - i.y)};
	while (i.x != target.x)
	{
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
		i.x += p_sign.x;
	}
	get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
	data->actor, *data->vel, &entity_list);
	while (i.y != target.y && _add(&i.y, &p_sign.y))
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

static inline short	get_mask(t_vector v)
{
	return (1 * (v.y < 0) \
		| 0b10 * (v.x > 0) \
		| 0b100 * (v.y > 0) \
		| 0b1000 * (v.x < 0));
}

static inline t_vector get_normal(short mask)
{
	t_vector vec;

	vec = (t_vector){((mask & 2) >> 1) - ((mask & 8) >> 3), \
		((mask & 4) >> 2) - (mask & 1)};
	if (vec.x && vec.y)
		vec = vector_multiply(vec, 0.70710678118);
	return (vec);
} 

static inline t_list *next_and_delete(t_list *node, void (*del)(void *))
{
	t_list *temp;

	temp = node->next;
	del(node->content);
	free(node);
	return (temp);
}

t_vector	solve_s_aabbs(struct s_data_pack *data, t_list **collision_list)
{
	t_list		*list;
	short		normal_mask;
	t_vector	impact_normal;
	double		col_tim;
	double		dot_prod;

	list = sort_collision_list(*collision_list);
	col_tim = ((t_swept_aabb *)list->next->content)->collision_time;
	normal_mask = get_mask(((t_swept_aabb *)list->next->content)->normal);
	list = next_and_delete(list, free);
	while (list && (col_tim == ((t_swept_aabb *)list->content)->collision_time))
	{
		normal_mask |= get_mask(((t_swept_aabb *)list->content)->normal);
		list = next_and_delete(list, free);
	}
	impact_normal = get_normal(normal_mask);
	dot_prod = ((*data->vel).x * impact_normal.y + (*data->vel).y * \
	impact_normal.x) * (1 - col_tim);
	*collision_list = list;
	return (vector_multiply(impact_normal, dot_prod));
}

static inline t_point map_size(t_map *map)
{
	return ((t_point){map->width, map->height});
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
			*data.vel = solve_s_aabbs(&data, &collision_list);
			if (!vector_cmpr(*data.vel, (t_vector){0, 0}))
				return (ft_lstclear(&collision_list, free));
			mov = line_in_area(i, get_tile(point_add(data.actor->position, \
			vector_to_point(*data.vel)), map), map_size(map));
			if (point_cmpr(mov.p2, gba.end))
				gba = gba_init(i, mov.p2);
			else
				mov = (t_line){gba.start, gba.end};
		}
		data.last_gba = gba_next(&gba, &i);
		ft_lstadd_back(&collision_list, check_more_tiles(i, &data, map));
	}
}

void	move_and_collide(t_actor *actor, t_vector velocity, t_map *map)
{
	t_point	current_tile;
	t_point	movemet_target;
	t_point	target_tile;

	current_tile = get_tile(actor->position, map);
	movemet_target = point_add(actor->position, vector_to_point(velocity));
	target_tile = get_tile(movemet_target, map);
	check_collisions_gba(line_in_area(current_tile, target_tile, (t_point)\
	{(int)map->width, (int)map->height}), (struct s_data_pack)\
	{(t_point){0, 0}, actor, &velocity, (t_point){0, 0}}, map);
	actor->position = point_add(actor->position, vector_to_point(velocity));
	actor->velocity = velocity;
}

#include "controller.h"

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
