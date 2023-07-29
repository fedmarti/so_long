/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_in_area.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:32:03 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/29 21:53:37 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line.h"
#include <math.h>
#include "../../libft/libft.h"

static t_point	point_clamp(t_point point, t_point min, t_point max)
{
	t_point	ret;

	ret.x = ft_clamp(point.x, min.x, max.x);
	ret.y = ft_clamp(point.y, min.y, max.y);
	return (ret);
}

static inline t_line	clamp_line(t_point	p1, t_point p2, t_line intersected, \
t_line clamped)
{
	t_line	corrected;

	if (!point_cmpr(p1, clamped.p1))
		corrected.p1 = p1;
	else if (p1.y < p2.y)
		corrected.p1 = intersected.p1;
	else
		corrected.p1 = intersected.p2;
	if (!point_cmpr(p2, clamped.p2))
		corrected.p2 = p2;
	else if (p1.y < p2.y)
		corrected.p2 = intersected.p2;
	else
		corrected.p2 = intersected.p1;
	return (corrected);
}

static inline t_line	vars_init(t_point *intersection, t_point p1, \
t_point p2, t_point size)
{
	double	slope;
	double	intercept;

	slope = (double)(p2.y - p1.y) / (double)(p2.x - p1.x);
	intercept = p1.y - (slope * p1.x);
	intersection[0] = (t_point){round(-intercept / slope), 0};
	intersection[1] = (t_point){size.x, round((double)size.x * slope \
	+ intercept)};
	intersection[2] = (t_point){round(((double)size.y - intercept) \
	/ slope), size.y};
	intersection[3] = (t_point){0, round(intercept)};
	return ((t_line){(t_point){0, 0}, (t_point){0, 0}});
}

t_line	get_intersections(t_point p1, t_point p2, t_point size)
{
	t_point	intersection[4];
	t_line	i_line;
	int		i;
	int		j;

	i_line = vars_init(intersection, p1, p2, size);
	i = 0;
	j = 0;
	while (i < 4)
	{
		if (!point_cmpr(intersection[i], point_clamp(intersection[i], \
		(t_point){0, 0}, size)))
		{
			if (j++ == 0)
				i_line.p1 = intersection[i];
			else
				i_line.p2 = intersection[i];
		}
		i++;
	}
	if (i_line.p1.y < i_line.p2.y)
		return (i_line);
	else
		return ((t_line){i_line.p2, i_line.p1});
}

t_line	line_in_area(t_point p1, t_point p2, t_point size)
{
	t_line	clamped;
	t_line	intersected;

	clamped.p1 = point_clamp(p1, (t_point){0, 0}, size);
	clamped.p2 = point_clamp(p2, (t_point){0, 0}, size);
	if (!point_cmpr(p1, clamped.p1) && !point_cmpr(p2, clamped.p2))
		return ((t_line){p1, p2});
	if (p1.y == p2.y || p1.x == p2.x)
		return (clamped);
	intersected = get_intersections(p1, p2, size);
	if (!point_cmpr(intersected.p1, (t_point){0, 0}) \
	&& !point_cmpr(intersected.p2, (t_point){0, 0}))
		return (intersected);
	return (clamp_line(p1, p2, intersected, clamped));
}

// Y - y1 = (X - x1) (y2 - y1) / (x2 - x1)
// incline = (y2 - y1) / (x2 - x1);
// (y - y1) = (x - x1) * incline

// y = (x - x1) * incline + y1
// (y - y1) / incline = (x - x1)

// x = (y - y1) / incline + x1

// y = a * x + b