/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/03 19:40:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include <stdlib.h>

t_point	vector_add(t_point	v1, t_point v2)
{
	t_point	result;

	result.x = v1.x + v2.x;
	result.y = v1.x + v2.y;
	return (result);
}

t_point	vector2(int x, int y)
{
	t_point	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

t_point	*vector2_pointer(t_point vector2)
{
	t_point	*pointer;

	pointer = malloc(sizeof(*pointer));
	if (pointer)
		*pointer = vector2;
	return (pointer);
}

double	vector_len(t_point	vector)
{
	double	len;

	len = pow((double) vector.x, 2) + pow((double) vector.y, 2);
	len = sqrt(len);
	return (len);
}

int	vector_cmpr(t_point a, t_point b)
{
	double	len;
	double	len2;

	len = vector_len(a);
	len2 = vector_len(b);
	if (len > len2)
		return (1);
	else if (len < len2)
		return (-1);
	return (0);
}
