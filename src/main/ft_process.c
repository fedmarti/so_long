/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:17:35 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "../../so_long.h"
#include "../graphics_logic/graphics.h"
#include "../player_controller/controller.h"
#include "../time/ft_time.h"

static void	paused_menu_logic(t_data *data)
{
	(void)data;
}

static void	in_game_logic(t_data *data)
{
	time_update(&data->time);
	data->map->player->velocity.y += GRAVITY \
	* (double)data->time.delta / (2 * ONE_SEC);
	player_controller(data);
	data->map->player->velocity.y += GRAVITY \
	* (double)data->time.delta / (2 * ONE_SEC);
	render_game(data);
}

void	program_state_machine(t_data *data)
{
	if (data->state == InGame)
		in_game_logic(data);
	else if (data->state == PausedMenu)
		paused_menu_logic(data);
	data->buffer = upscale(data->buffer, data->pre_buffer);
	mlx_put_image_to_window \
	(data->mlx, data->mlx_window, data->buffer->img, 0, 0);
}

int	ft_process(void *data)
{
	program_state_machine(data);
	lock_framerate(((t_data *)data)->time.last_frame);
	return (0);
}
