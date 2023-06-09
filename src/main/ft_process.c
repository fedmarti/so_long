/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/06 20:51:28 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "../../so_long.h"
#include "../graphics_logic/graphics.h"
#include "../player_controller/controller.h"

int	ft_process(void *data)
{
	//enemy_logic()
	// ((t_data *)data)->map->player->sprites = put_solid_color(((t_data *)data)->map->player->sprites, 0x694299);
	player_controller(data);
	render_frame(data);
	usleep(16666);
	if ((((t_data *) data)->map->player->position.x) > 1000 || (((t_data *) data)->map->player->position.y) > 1000 || (((t_data *) data)->map->player->position.x) < 0 || (((t_data *) data)->map->player->position.y) < 0)
		pause();
	return (0);
}
