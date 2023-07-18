/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:46:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/17 21:02:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../t_point/point.h"
# include "line.h"
# include "rectangle.h"
# include <stdbool.h>

typedef struct s_hit
{
	t_point	origin;
	t_point	intersection;	
	bool	collision;
}	t_hit;

struct s_hit	raycast(t_point p1, t_point p2, t_point p3, t_point p4);
struct s_hit	raycast_to_rectangle(t_point from, \
t_point to, t_point rec_pos, t_point rec_size);
t_hit			rec_shoot_ray(t_rectangle actor, \
t_point direction_vector, t_rectangle target);
bool			is_h2_closer(t_hit h1, t_hit h2);

#endif
