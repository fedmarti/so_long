/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions_gba.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:51:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:48:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "controller.h"
#include "../2d_geometry/gba_line_draw.h"
#include "../2d_geometry/line.h"
#include "../2d_geometry/rectangle.h"
#include "../map/map.h"

void	update_gba(t_gba_data *gba, struct s_data_pack *data, \
t_point i, t_map *map)
{
	t_line	nl;

	nl = line_in_area(i, get_tile(point_add(data->actor->position, \
	vector_to_point(*data->vel)), map), (t_point){map->width, map->height});
	if (point_cmpr(nl.p2, gba->end))
	{
		*gba = gba_init(i, nl.p2);
	}
}

t_list		*check_surrounding_area(t_point tile, struct s_data_pack \
*data, t_map *map);
t_vector	solve_s_aabbs(struct s_data_pack *data, t_list **collision_list);
t_list		*check_more_tiles(t_point tile, struct s_data_pack *data, \
t_map *map);

//uses the generalized bresemham algorithm to select a line of map tiles
//to check, starting from the current tile, 
//in the direction of the velocity vector
void	check_collisions_gba(t_line mov, struct s_data_pack \
data, t_map *map)
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
			if (!data.vel->x && !data.vel->y)
				return ;
			update_gba(&gba, &data, i, map);
			collision_list = check_surrounding_area(i, &data, map);
			data.last_gba = gba_next(&gba, &i);
			continue ;
		}
		data.last_gba = gba_next(&gba, &i);
		ft_lstadd_back(&collision_list, check_more_tiles(i, &data, map));
	}
}
