/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:16:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_structs.h"

t_point	point_subtract(t_point p1, t_point p2)
{
	t_point	result;

	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	return (result);
}

t_point	point_multiply(t_point point, double factor)
{
	t_point	result;

	result.x = point.x * factor;
	result.y = point.y * factor;
	return (result);
}

t_point	point_divide(t_point point, int divisor)
{
	t_point	result;

	result.x = point.x / divisor;
	result.y = point.y / divisor;
	return (result);
}
