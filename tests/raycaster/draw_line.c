/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 22:38:36 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/28 17:46:12 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "code_units/graphics_logic.h"
#include "../../libft/libft.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);

void	draw_line_dda(t_image *img, t_point start, t_point end, unsigned int color)
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

void	draw_line_bresenham(t_image *img, t_point start, t_point end, unsigned int color)
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
		// put_pixel_to_img(img, ft_clamp(point.x, 0, img->size.x), ft_clamp(point.y, 0, img->size.y), color);
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
