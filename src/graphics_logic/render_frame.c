/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:34:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:01:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "graphics.h"

static t_image	*render_ui(t_data *data)
{
	return (data->pre_buffer);
}

void	render_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_window);
	data->pre_buffer = put_solid_color(data->pre_buffer, 0x00330866);
	data->pre_buffer = render_actors(data);
	data->pre_buffer = render_ui(data);
}
