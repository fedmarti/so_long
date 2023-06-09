/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 21:46:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/10 19:26:49 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "code_units/point.h"
# include <stdbool.h>

typedef struct s_hit
{
	t_point	intersection;
	bool	collision;
}	t_hit;

struct s_hit	raycast(t_point p1, t_point p2, t_point p3, t_point p4);

#endif