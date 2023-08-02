/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:29:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../macro_headers/general_settings.h"
#include "../graphics_logic/graphics.h"
#include "../2d_geometry/rectangle.h"
#include "controller.h"
#include "swept_aabb.h"
#include <math.h>
#include "controller.h"
#include "../map/map.h"
#include "../2d_geometry/line.h"

t_list		*check_surrounding_area(t_point tile, struct s_data_pack \
*data, t_map *map);
t_list		*check_collision_type(struct s_data_pack *data, \
t_list *collision_list);
t_vector	solve_s_aabbs(struct s_data_pack *data, t_list **collision_list);
void		check_collisions_gba(t_line mov, struct s_data_pack \
data, t_map *map);

t_vector	get_player_direction(t_input input)
{
	t_vector	direction;

	direction = vector2(input.right - input.left, 0 * (input.down - input.up));
	if (direction.x && direction.y)
		direction = vector_multiply(direction, 0.70710678118);
	return (direction);
}

void	reintroduce_into_map(t_actor *actor, t_map *map, t_point current_tile)
{
	t_list	*temp;

	temp = ft_lstnew(actor);
	if (!temp)
	{
		actor_free(actor, map, map->data->mlx);
		ft_quit(map->data);
	}
	ft_lstadd_back(&map->tiles[current_tile.y][current_tile.x].entity_list, \
	temp);
}

void	move_and_collide(t_actor *actor, t_vector velocity, \
t_map *map, t_data *data)
{
	t_point	current_tile;
	t_point	movemet_target;
	t_point	target_tile;

	current_tile = get_tile(actor->position, map);
	if (current_tile.x >= 0 && current_tile.x < (int)map->width && \
	current_tile.y >= 0 && current_tile.y < (int)map->height)
		free(ft_lstpop_one(actor, \
		&map->tiles[current_tile.y][current_tile.x].entity_list));
	movemet_target = point_add(actor->position, vector_to_point(velocity));
	target_tile = get_tile(movemet_target, map);
	check_collisions_gba(line_in_area(current_tile, target_tile, (t_point) \
	{(int)map->width, (int)map->height}), (struct s_data_pack) \
	{(t_point){0, 0}, actor, &velocity, (t_point){0, 0}, map, data}, map);
	actor->position = point_add(actor->position, vector_to_point(velocity));
	actor->velocity = velocity;
	current_tile = get_tile(actor->position, map);
	if (current_tile.x >= 0 && current_tile.x < (int)map->width && \
	current_tile.y >= 0 && current_tile.y < (int)map->height)
		reintroduce_into_map(actor, map, current_tile);
}

void	player_controller(t_data *data)
{
	t_vector	direction;
	t_vector	velocity;

	direction = get_player_direction(data->input);
	velocity = vector_multiply(direction, (PLAYER_SPEED + (DASH_BOOST \
	* data->input.shift_left)));
	velocity = vector_multiply(velocity, ((double)data->time.delta / ONE_SEC));
	velocity.y += data->map->player->velocity.y;
	if (data->input.space && is_on_ground(data->map->player, data->map))
		velocity.y = -JUMP;
	move_and_collide(data->map->player, velocity, data->map, data);
}
