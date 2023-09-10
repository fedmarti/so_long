/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_fraction_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 23:14:52 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/08 23:20:29 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_internal.h"

t_img_fraction	get_img_fraction(t_image *big, t_point size, t_point offset, \
				t_point position)
{
	t_img_fraction	fraction;

	fraction.addr = big->addr + \
	(position.y * big->line_length + position.x * (big->bits_per_pixel >> 3));
	fraction.bits_per_pixel = big->bits_per_pixel;
	fraction.endian = big->endian;
	fraction.line_length = big->line_length;
	fraction.offset = offset;
	fraction.size = size;
	fraction.whole_image_size = big->size;
	return (fraction);
}
