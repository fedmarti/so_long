/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_surrounding_area.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:37:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:16:05 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "swept_aabb.h"

static inline int	_add(int *a, int *b)
{
	*a += *b;
	return (1);
}

static inline void	_vars_init(t_point *target, struct s_data_pack *data, \
t_point *i, t_point tile)
{
	i->x = -(data->last_gba.x != 0);
	i->y = -(data->last_gba.y != 0);
	*target = (t_point){data->area_size.x - 1, data->area_size.y - 1};
	*target = (t_point){target->x * -i->x, target->y * -i->y};
	i->x -= i->x * (tile.x == 0);
	i->y -= i->y * (tile.y == 0);
	if (data->last_gba.x < 0)
		ft_swap_i(&i->x, &target->x);
	if (data->last_gba.y < 0)
		ft_swap_i(&i->y, &target->y);
}

void	get_s_aabbs(t_list *tile_list, t_actor *actor, \
t_vector vel, t_list **entity_list);

t_list	*check_more_tiles(t_point tile, struct s_data_pack *data, t_map *map)
{
	t_point	i;
	t_list	*entity_list;
	t_point	target;
	t_point	p_sign;

	_vars_init(&target, data, &i, tile);
	entity_list = NULL;
	p_sign = (t_point){ft_sign(target.x - i.x), ft_sign(target.y - i.y)};
	while (i.x != target.x && tile.y + i.y < (int)map->height \
	&& tile.x + i.x < (int)map->width)
	{
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
		i.x += p_sign.x;
	}
	if (tile.y + i.y < (int)map->height && tile.x + i.x < (int)map->width)
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
	while (i.y != target.y && _add(&i.y, &p_sign.y) \
	&& tile.y + i.y < (int)map->height && tile.x + i.x < (int)map->width)
		get_s_aabbs(map->tiles[tile.y + i.y][tile.x + i.x].entity_list, \
		data->actor, *data->vel, &entity_list);
	return (entity_list);
}

static t_point	vars_init(struct s_data_pack *data, t_point *i, t_point tile)
{
	data->area_size = point_divide(data->actor->size, TILE_SIZE);
	data->area_size = (t_point){!data->area_size.x + data->area_size.x, \
	!data->area_size.y + data->area_size.y};
	data->area_size = point_add(data->area_size, (t_point){2, 2});
	i->y = -1;
	i->y += (abs(i->y + tile.y) * (i->y + tile.y < 0));
	i->x = -1;
	i->x += (abs(i->x + tile.x) * (i->x + tile.x < 0));
	return (data->area_size);
}

t_list	*check_surrounding_area(t_point tile, struct s_data_pack \
*data, t_map *map)
{
	t_list		*entity_list;
	t_point		tile_area;
	t_point		i;

	entity_list = NULL;
	tile_area = vars_init(data, &i, tile);
	while (i.y < tile_area.y && i.y + tile.y < (int) map->height)
	{
		i.x = -1 + (abs(tile.x - 1) * (tile.x < 1));
		while (i.x < tile_area.x && i.x + tile.x < (int) map->width)
		{
			get_s_aabbs(map->tiles[i.y + tile.y][i.x + tile.x].entity_list, \
			data->actor, *data->vel, &entity_list);
			i.x++;
		}
		i.y++;
	}
	return (entity_list);
}
