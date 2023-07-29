/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/29 18:26:33 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "raycaster.h"
#include "../code_units/graphics_logic.h"
#include "../code_units/player_controller.h"
# include "../../src/2d_geometry/line.h"
# include "../../src/2d_geometry/raycast.h"


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

static inline void	get_lines(t_line *lines, t_point rec_pos, t_point rec_size)
{
	lines[0] = (t_line){rec_pos, (t_point){rec_pos.x + rec_size.x, rec_pos.y}};
	lines[1] = (t_line)\
	{(t_point){rec_pos.x + rec_size.x, rec_pos.y}, \
	(t_point){rec_pos.x + rec_size.x, rec_pos.y + rec_size.y}};
	lines[2] = (t_line)\
	{(t_point){rec_pos.x + rec_size.x, rec_pos.y + rec_size.y},\
	(t_point){rec_pos.x, rec_pos.y + rec_size.y}};
	lines[3] = (t_line){{rec_pos.x, rec_pos.y + rec_size.y}, rec_pos};
}


void	draw_rectangles(t_image *img, rc_p_struct *raycast_data)
{
	t_list	*rec_list;

	rec_list = raycast_data->rec_list;
	while (rec_list)
	{
		t_rectangle rec = *((t_rectangle *)rec_list->content);
		t_line	lines[4];
		get_lines(lines, rec.pos, rec.size);
		for (int i = 0; i < 4; i++)
			draw_line_gba(img, lines[i].p1, lines[i].p2, 0x00ffffff);
		rec_list = rec_list->next;
	}
}

bool	len_check(t_point origin, t_point p1, t_point p2)
{
	p1 = point_subtract(p1, origin);
	p2 = point_subtract(p2, origin);
	return (point_len(p1) > point_len(p2));
}

t_hit	ray_hit(rc_p_struct *raycast_data)
{
	t_list	*rec_list;
	t_line	ray;
	t_hit	hit = (t_hit){(t_point){0,0},(t_point){0,0}, false};

	ray = (t_line){raycast_data->position, raycast_data->mouse_position};
	rec_list = raycast_data->rec_list;
	while (rec_list)
	{
		t_hit	temp_hit;
		t_rectangle rec = *((t_rectangle *)rec_list->content);
		temp_hit = raycast_to_rectangle(ray.p1, ray.p2, rec.pos, rec.size);
		if (temp_hit.collision)
		{
			if (!hit.collision || len_check(raycast_data->position, hit.intersection, temp_hit.intersection))
				hit = temp_hit; 
		}
		rec_list = rec_list->next;
	}
	return (hit);
}



int	ft_process(void *data)
{
	t_data	*d = data;

	mlx_mouse_get_pos(d->mlx, d->mlx_window, &d->raycaster_struct->mouse_position.x, &d->raycaster_struct->mouse_position.y);
	d->raycaster_struct->position = point_add(d->raycaster_struct->position, point2((d->input.right - d->input.left) * 3, (d->input.down - d->input.up) * 3));
		mlx_clear_window(d->mlx, d->mlx_window);
	d->pre_buffer = put_solid_color(d->pre_buffer, 0x00330866);
	d->buffer = upscale(d->buffer, d->pre_buffer);
	draw_rectangles(d->buffer, d->raycaster_struct);
	unsigned int color = 0xFFFFFF;
	t_line	line = {point_clamp(d->raycaster_struct->position, point2(0,0), d->buffer->size), point_clamp(d->raycaster_struct->mouse_position, point2(0,0), d->buffer->size)};
	if (d->raycaster_struct->rec_list)
	{
		t_rectangle rec = *(t_rectangle *)d->raycaster_struct->rec_list->content;
		line = (t_line){point_subtract(line.p1, rec.pos), point_subtract(line.p2, rec.pos)};
		line = line_in_area(line.p1, line.p2, rec.size);
		line = (t_line){point_add(line.p1, rec.pos), point_add(line.p2, rec.pos)};
	}
	line = (t_line){point_clamp(line.p1, point2(0,0), d->buffer->size), point_clamp(line.p2, point2(0,0), d->buffer->size)};
	draw_line_gba(d->buffer, line.p1, line.p2, color);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	
	usleep(16666);
	return (0);
}
