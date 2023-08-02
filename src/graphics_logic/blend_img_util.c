/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:40:28 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:47:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blend_img_util.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);
void	*get_pixel(t_image *img, int x, int y);
int		get_pointer_offset_img(t_image *img, int x, int y);

// if the image position is negative (out of the frame, offset is calculated)
// to skip drawin the parts out of sight
t_point	get_offset(t_point	position)
{
	t_point	offset;

	offset = point2(0, 0);
	if (position.x < 0)
		offset.x = -position.x;
	if (position.y < 0)
		offset.y = -position.y;
	return (offset);
}

char	*vars_init(t_p data)
{
	*data.position = point_add(*data.position, data.src->offset);
	*data.offset = get_offset(*data.position);
	data.i->y = 0;
	*data.dst_pixl = data.dst->addr + get_pointer_offset_img(data.dst, \
	data.position->x, data.position->y);
	return (data.src->addr + get_pointer_offset_img(data.src, \
	data.offset->x, data.offset->y));
}
