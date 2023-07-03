/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/27 22:29:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "raycaster.h"
#include "../code_units/graphics_logic.h"
#include "../code_units/player_controller.h"

void	draw_line_bresenham(t_image *img, t_point start, t_point end, unsigned int color);

t_point	point_clamp(t_point point, t_point min, t_point max)
{
	t_point	ret;

	ret.x = ft_clamp(point.x, min.x, max.x);
	ret.y = ft_clamp(point.y, min.y, max.y);
	return (ret);
}

int	ft_process(void *data)
{
	t_data	*d = data;

	mlx_mouse_get_pos(d->mlx, d->mlx_window, &d->raycaster_struct->mouse_position.x, &d->raycaster_struct->mouse_position.y);
	d->raycaster_struct->position = point_add(d->raycaster_struct->position, point2((d->input.right - d->input.left) * 3, (d->input.down - d->input.up) * 3));
		mlx_clear_window(d->mlx, d->mlx_window);
	d->pre_buffer = put_solid_color(d->pre_buffer, 0x00330866);
	d->buffer = upscale(d->buffer, d->pre_buffer);
	draw_line_bresenham(d->buffer, point_clamp(d->raycaster_struct->position, point2(0,0), d->buffer->size), point_clamp(d->raycaster_struct->mouse_position, point2(0,0), d->buffer->size), 0x00ffffff);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	usleep(16666);
	return (0);
}
