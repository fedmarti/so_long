/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:17:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/10 19:26:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "code_units/point.h"
#include "raycast.h"

struct s_hit	raycast(t_point p1, t_point p2, t_point p3, t_point p4)
{
	int		den;
	t_point	hit;
	double	t;
	double	u;

	den = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
	if (!den)
		return ((t_hit){p1, false});
	t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) \
	/ (double)den;
	u = -1 * ((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) \
	/ (double)den;
	if (t > 0 && t < 1 && u > 0 && u < 1)
	{
		hit.x = p1.x + t * (p2.x - p1.x);
		hit.y = p1.y + t * (p2.y - p1.y);
		return ((t_hit){hit, true});
	}
	return ((t_hit){p1, false});
}
