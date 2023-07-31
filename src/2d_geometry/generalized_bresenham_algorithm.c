/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generalized_bresenham_algorithm.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:42:02 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/30 19:55:21 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_point/point.h"
#include "../../libft/libft.h"
#include "gba_line_draw.h"

//initializes and returns the struct for the algorithm
t_gba_data	gba_init(t_point start, t_point end)
{
	t_gba_data	data;

	data.delta = point_subtract(end, start);
	data.sign = point2(ft_sign(data.delta.x), ft_sign(data.delta.y));
	data.ex_change = (ft_abs(data.delta.y) > ft_abs(data.delta.x));
	data.delta = (t_point){abs_max_signed(data.delta.x, data.delta.y), \
	abs_min_signed(data.delta.x, data.delta.y)};
	data.e = 2 * ft_abs(data.delta.y) - ft_abs(data.delta.x);
	data.start = start;
	data.end = end;
	return (data);
}

//calculates the next point increments *current and returns the increment
t_point	gba_next(t_gba_data *d, t_point *current)
{
	t_point	increment;

	increment = (t_point){0, 0};
	if (!point_cmpr(*current, d->end))
		return (increment);
	while (d->e >= 0)
	{
		increment = point2(d->ex_change * d->sign.x, !d->ex_change * d->sign.y);
		d->e -= ft_abs(2 * d->delta.x);
	}
	increment = (t_point){!d->ex_change * d->sign.x + increment.x, \
	d->ex_change * d->sign.y + increment.y};
	*current = point_add(*current, increment);
	d->e += ft_abs(2 * d->delta.y);
	return (increment);
}
