/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_controller.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:03:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 03:09:47 by fedmarti         ###   ########.fr       */
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

void	player_controller(t_data *data)
{
	t_vector direction;

	direction = get_player_direction(data->input);
	*data->pos = point_add(*data->pos, vector_to_point(vector_multiply(direction , (PLAYER_SPEED + (DASH_BOOST * data->input.shift_left)))));
	//HANDLE COLLISIONS
}