/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/18 22:38:47 by fedmarti         ###   ########.fr       */
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
	//render_paused_menu(data);
	(void)data;
}

static void	in_game_logic(t_data *data)
{
	time_update(&data->time);
	player_controller(data);
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
	//enemy_logic()
	// ((t_data *)data)->map->player->sprites = put_solid_color(((t_data *)data)->map->player->sprites, 0x694299);
	lock_framerate(((t_data *)data)->time.last_frame);
	return (0);
}
