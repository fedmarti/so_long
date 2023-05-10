/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:28:21 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 02:16:41 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/t_point/point.h"

t_point	ft_get_next_direction(void)
{
	static t_point	dir;

	if (!point_cmpr(dir, point2(0, -1)))
		dir = point2(1, 0);
	else if (!point_cmpr(dir, point2(1, 0)))
		dir = point2(0, 1);
	else if (!point_cmpr(dir, point2(0, 1)))
		dir = (point2(-1, 0));
	else
		dir = point2(0, -1);
	return (dir);
}
