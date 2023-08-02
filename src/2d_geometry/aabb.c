/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:08:04 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:30:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_point/point.h"
#include "rectangle.h"
#include <stdbool.h>

bool	aabb(t_point p1, t_point p2, t_point p3, t_point p4)
{
	return (p1.x < p4.x && p2.x > p3.x && p1.y < p4.y && p2.y > p3.y);
}

bool	aabb_rectangles(t_rectangle rec1, t_rectangle rec2)
{
	return (aabb(rec1.pos, point_add(rec1.pos, rec1.size), \
	rec2.pos, point_add(rec2.pos, rec2.size)));
}
