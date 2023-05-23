/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:34:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 00:16:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "graphics.h"

void	render_frame(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_window);
	data->pre_buffer = put_solid_color(data->pre_buffer, 0x0044FF00);
	data->pre_buffer = render_actors(data);
	data->buffer = upscale(data->buffer, data->pre_buffer);
	mlx_put_image_to_window \
	(data->mlx, data->mlx_window, data->buffer->img, 0, 0);
}
