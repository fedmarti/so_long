/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 19:36:42 by fedmarti         ###   ########.fr       */
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
	player_controller(data);
	render_frame(data);
	usleep(10000);
	if ((((t_data *) data)->map->player->position.x) > 1000 || (((t_data *) data)->map->player->position.y) > 1000)
		pause();
	return (0);
}
