/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_fraction_util.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:19:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 19:01:27 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blend_img_fraction_util.h"

static t_point	get_offset(t_point	position)
{
	t_point	offset;

	offset = point2(0, 0);
	if (position.x < 0)
		offset.x = -position.x;
	if (position.y < 0)
		offset.y = -position.y;
	return (offset);
}

char	*vars_init_(t_p data)
{
	*data.position = point_add(*data.position, data.src->offset);
	*data.offset = get_offset(*data.position);
	data.i->y = 0;
	*data.dst_pixl = data.dst->addr + (data.position->y \
	* data.dst->line_length + data.position->x \
	* (data.dst->bits_per_pixel >> 3));
	return (data.src->addr + (data.offset->y * data.src->line_length + \
	data.offset->x * (data.src->bits_per_pixel >> 3)));
}
