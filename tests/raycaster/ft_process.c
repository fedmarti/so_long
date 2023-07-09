/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/09 23:32:47 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "raycaster.h"
#include "../code_units/graphics_logic.h"
#include "../code_units/player_controller.h"

void	draw_line_bres\
(t_image *img, t_point start, t_point end, unsigned int color);
void \
	draw_line_gba(t_image *img, t_point start, t_point end, unsigned int color);

t_point	point_clamp(t_point point, t_point min, t_point max)
{
	t_point	ret;

	ret.x = ft_clamp(point.x, min.x, max.x);
	ret.y = ft_clamp(point.y, min.y, max.y);
	return (ret);
}


void	draw_walls(t_image *img, rc_p_struct *raycast_data)
{
	t_list	*wall_list;

	wall_list = raycast_data->line_list;
	while (wall_list)
	{
		t_line line = *((t_line *)wall_list->content);
		draw_line_gba(img, line.start, line.end, 0x00ffffff);
		wall_list = wall_list->next;
	}
}

t_point	raycast(t_point p1, t_point p2, t_point p3, t_point p4);

bool	hit(rc_p_struct *raycast_data)
{
	t_list	*wall_list;
	t_line	ray;

	ray = (t_line){raycast_data->position, raycast_data->mouse_position};
	wall_list = raycast_data->line_list;
	while (wall_list)
	{
		t_line line = *((t_line *)wall_list->content);
		if (point_cmpr(raycast(ray.start, ray.end, line.start, line.end), ray.start))
			return (true);
		wall_list = wall_list->next;
	}
	return (false);
}

int	ft_process(void *data)
{
	t_data	*d = data;

	mlx_mouse_get_pos(d->mlx, d->mlx_window, &d->raycaster_struct->mouse_position.x, &d->raycaster_struct->mouse_position.y);
	d->raycaster_struct->position = point_add(d->raycaster_struct->position, point2((d->input.right - d->input.left) * 3, (d->input.down - d->input.up) * 3));
		mlx_clear_window(d->mlx, d->mlx_window);
	d->pre_buffer = put_solid_color(d->pre_buffer, 0x00330866);
	d->buffer = upscale(d->buffer, d->pre_buffer);
	draw_walls(d->buffer, d->raycaster_struct);
	unsigned int color;
	if (hit(d->raycaster_struct))
		color = 0xFF0000;
	else
		color = 0xffffff;
	draw_line_gba(d->buffer, point_clamp(d->raycaster_struct->position, point2(0,0), d->buffer->size), point_clamp(d->raycaster_struct->mouse_position, point2(0,0), d->buffer->size), color);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	
	usleep(16666);
	return (0);
}
