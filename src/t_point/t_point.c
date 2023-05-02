/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 21:46:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	vector2(unsigned int x, unsigned int y)
{
	t_point	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
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
