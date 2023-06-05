/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_vector_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:36:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/25 23:49:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_structs.h"
#include <math.h>

double	vector_len(t_vector vector)
{
	double	len;

	len = pow(vector.x, 2) + pow(vector.y, 2);
	len = sqrt(len);
	return (len);
}

t_vector	vector_divide(t_vector vector, double divisor)
{	
	vector.x /= divisor;
	vector.y /= divisor;
	return (vector);
}

t_vector	vector_normalize(t_vector vector)
{
	return (vector_divide(vector, vector_len(vector)));
}

t_vector	vector_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return (result);
}

int	vector_cmpr(t_vector v1, t_vector v2)
{
	return ((int)vector_len(vector_subtract(v1, v2)));
}
