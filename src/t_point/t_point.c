/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 02:17:22 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include <stdlib.h>

t_point	point_add(t_point	v1, t_point v2)
{
	t_point	result;

	result.x = v1.x + v2.x;
	result.y = v1.x + v2.y;
	return (result);
}

t_point	point2(int x, int y)
{
	t_point	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_point	*point2_pointer(t_point point2)
{
	t_point	*pointer;

	pointer = malloc(sizeof(*pointer));
	if (pointer)
		*pointer = point2;
	return (pointer);
}

double	point_len(t_point	vector)
{
	double	len;

	len = pow((double) vector.x, 2) + pow((double) vector.y, 2);
	len = sqrt(len);
	return (len);
}

int	point_cmpr(t_point a, t_point b)
{
	double	len;
	double	len2;

	len = point_len(a);
	len2 = point_len(b);
	if (len > len2)
		return (1);
	else if (len < len2)
		return (-1);
	return (0);
}
