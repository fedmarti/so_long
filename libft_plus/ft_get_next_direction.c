/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_direction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:28:21 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:51:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_point/point.h"

t_point	ft_get_next_direction(void)
{
	static t_point	dir;

	if (!vector_cmpr(dir, vector2(0, -1)))
		dir = vector2(1, 0);
	else if (!vector_cmpr(dir, vector2(1, 0)))
		dir = vector2(0, 1);
	else if (!vector_cmpr(dir, vector2(0, 1)))
		dir = (vector2(-1, 0));
	else
		dir = vector2(0, -1);
	return (dir);
}
