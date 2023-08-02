/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:43:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 23:30:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RECTANGLE_H
# define RECTANGLE_H

# include "../t_point/point.h"
# include "line.h"
# include <stdbool.h>

typedef struct s_rectangle
{
	t_point	pos;
	t_point	size;
}	t_rectangle;

bool	aabb(t_point p1, t_point p2, t_point p3, t_point p4);
bool	aabb_rectangles(t_rectangle rec1, t_rectangle rec2);
t_line	line_in_area(t_point p1, t_point p2, t_point size);

#endif