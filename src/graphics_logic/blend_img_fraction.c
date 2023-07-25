/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_fraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:08:46 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/25 19:35:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_internal.h"
#include "colors.h"
#include "../t_point/point.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);
void	*get_pixel(t_image *img, int x, int y);
int		get_pointer_offset_img(t_image *img, int x, int y);

// if the image position is negative (out of the frame, offset is calculated)
// to skip drawin the parts out of sight
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

static inline void	blend(char	*dest, char	*source, \
	unsigned int (*blend_mode)(unsigned int, unsigned int))
{
	*(unsigned int *)dest = \
	blend_mode(*(unsigned int *)dest, *(unsigned int *)source);
}

static inline void	next_line(char **addr, t_image *img, int printed_pixels)
{
	*addr += img->line_length - printed_pixels * (img->bits_per_pixel >> 3);
}

static inline void next_line_f(char **addr, t_img_fraction *img, \
								int printed_pixels)
{
	*addr += img->line_length - printed_pixels * (img->bits_per_pixel >> 3);
}

void	blend_img_fraction(t_img_fraction *src, t_image *dst, t_point position, \
	unsigned int (*blend_mode)(unsigned int, unsigned int))
{
	t_point	i;	
	t_point	offset;
	char	*dst_pixl;
	char	*src_pixl;

	if (!src || !dst || !src->addr || !dst->addr \
	|| position.x + src->size.x < 0 || position.y + src->size.y < 0)
		return ;
	position = point_add(position, src->offset);
	offset = get_offset(position);
	i.y = 0;
	dst_pixl = dst->addr + get_pointer_offset_img(dst, position.x, position.y);
	src_pixl = src->addr + (offset.y * src->line_length + offset.x * (src->bits_per_pixel >> 3));
	while (position.y + i.y + offset.y < dst->size.y && i.y + offset.y < src->size.y)
	{
		i.x = 0;
		while (position.x + i.x + offset.x < dst->size.x && i.x + offset.x < src->size.x)
		{
			blend(dst_pixl, src_pixl, blend_mode);
			dst_pixl += dst->bits_per_pixel >> 3;
			src_pixl += src->bits_per_pixel >> 3;
			i.x++;
		}
		next_line(&dst_pixl, dst, i.x);
		next_line_f(&src_pixl, src, i.x);
		i.y++;
	}
}
