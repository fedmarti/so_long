/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:46:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/14 22:54:23 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "../t_point/point.h"
# include "line.h"
# include <stdbool.h>

typedef struct s_hit
{
	t_point	intersection;
	t_point	origin;
	bool	collision;
}	t_hit;

struct s_hit	raycast(t_point p1, t_point p2, t_point p3, t_point p4);
struct s_hit	raycast_to_rectangle (t_point from, t_point to, t_point rec_pos, t_point rec_size);
bool			is_h2_closer(t_hit h1, t_hit h2);

#endif