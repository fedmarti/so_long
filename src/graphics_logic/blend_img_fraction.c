/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_fraction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 00:08:46 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 19:02:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "blend_img_fraction_util.h"

// if the image position is negative (out of the frame, offset is calculated)
// to skip drawin the parts out of sight

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

static inline void	next_line_f(char **addr, t_img_fraction *img, \
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
	src_pixl = vars_init_((t_p){&i, &offset, src, dst, &position, &dst_pixl});
	while (position.y + i.y + offset.y < dst->size.y && \
	i.y + offset.y < src->size.y)
	{
		i.x = 0;
		while (position.x + i.x + offset.x < dst->size.x \
		&& i.x + offset.x < src->size.x)
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
