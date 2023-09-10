/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:34:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 18:10:49 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "graphics_internal.h"
#include "graphics.h"
#include "../counter/counter.h"

t_image	*get_counter_graphics(void *counter);

static t_image	*render_ui(t_data *data)
{
	t_image	*counter_img;
	t_point	cntr_pos;

	counter_img = get_counter_graphics(data->counter);
	cntr_pos.x = (data->pre_buffer->size.x - counter_img->size.x) / 2;
	cntr_pos.y = 0;
	blend_images(counter_img, data->pre_buffer, cntr_pos, overlay);
	return (data->pre_buffer);
}

void	render_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_window);
	data->pre_buffer = put_solid_color(data->pre_buffer, 0x00330866);
	data->pre_buffer = render_actors(data);
	data->pre_buffer = render_ui(data);
}
