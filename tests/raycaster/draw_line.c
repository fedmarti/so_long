/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:38:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/09 21:51:04 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "code_units/graphics_logic.h"
#include "../../libft/libft.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);

void \
	draw_line_dda(t_image *img, t_point start, t_point end, unsigned int color)
{
	int			steps;
	t_vector	increment;
	t_vector	draw_pos;

	steps = abs_max(end.x - start.x, end.x - start.x);
	draw_pos = point_to_vector(start);
	increment = \
	vector_divide(point_to_vector(point_subtract(end, start)), (double)steps);
	while (steps--)
	{
		put_pixel_to_img(img, round(draw_pos.x), round(draw_pos.y), color);
		draw_pos = vector_add(draw_pos, increment);
	}
}

void \
	draw_line_bres(t_image *img, t_point start, t_point end, unsigned int color)
{
	int		decision_parameter;
	int		dx;
	int		dy;
	t_point	point;

	point = start;
	decision_parameter = 2 * (end.y - point.y) - (end.x - point.x);
	while (point_cmpr(point, end))
	{
		dx = end.x - point.x;
		dy = end.y - point.y;
		put_pixel_to_img(img, point.x, point.y, color);
		if (decision_parameter < 0)
		{
			decision_parameter += 2 * dy;
			point.x += 1;
		}
		else
		{
			decision_parameter += 2 * dy - 2 * dx;
			point = point_add(point, point2(1, 1));
		}
	}
	put_pixel_to_img(img, point.x, point.y, color);
}

static inline t_point	abs_delta(t_point delta)
{
	t_point	abs_delta;

	abs_delta.x = abs_max_signed(delta.x, delta.y);
	abs_delta.y = abs_min_signed(delta.x, delta.y);
	return (abs_delta);
}

//generalized bresenham algorithm
//sometimes it skips the last pixel
//good enough tbh
void \
	draw_line_gba(t_image *img, t_point start, t_point end, unsigned int color)
{
	t_point	delta;
	t_point	point;
	t_point	sign;
	int		ex_change;
	int		e;

	delta = point_subtract(end, start);
	point = start;
	sign = point2(ft_sign(delta.x), ft_sign(delta.y));
	ex_change = (ft_abs(delta.y) > ft_abs(delta.x));
	delta = abs_delta(delta);
	e = 2 * ft_abs(delta.y) - ft_abs(delta.x);
	while (point_cmpr(point, end))
	{
		put_pixel_to_img(img, point.x, point.y, color);
		while (e >= 0)
		{
			point = \
			point_add(point2(ex_change * sign.x, !ex_change * sign.y), point);
			e -= ft_abs(2 * delta.x);
		}
		point = \
		point_add(point2(!ex_change * sign.x, ex_change * sign.y), point);
		e += ft_abs(2 * delta.y);
	}
}
