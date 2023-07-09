/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:17:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/09 23:48:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "code_units/point.h"

t_point	raycast(t_point p1, t_point p2, t_point p3, t_point p4)
{
	int	den;
	double	t;
	double u;

	den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	if (!den)
		return (p1);
	t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / (double)den;
	u = -1 * ((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / (double)den;
	if (t > 0 && t < 1 && u > 0 && u < 1)
		return (p2);
	return (p1);
}
