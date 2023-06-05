/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:20:24 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/25 23:55:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_structs.h"

t_vector	vector2(double x, double y)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

t_vector	vector_multiply(t_vector vector, double factor)
{	
	vector.x *= factor;
	vector.y *= factor;
	return (vector);
}

t_point	vector_to_point(t_vector v)
{
	t_point	point;

	point.x = (int)v.x;
	point.y = (int)v.y;
	return (point);
}

t_vector	point_to_vector(t_point p)
{
	t_vector vector;

	vector.x = (double)p.x;
	vector.y = (double)p.y;
	return (vector);
}
