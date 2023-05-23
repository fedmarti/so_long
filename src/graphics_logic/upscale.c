/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 04:37:40 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/22 18:28:26 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static inline void	quick_put_pix(unsigned int color, t_image *img, \
								unsigned int x, unsigned int y)
{
	*(unsigned int *)&(img->addr \
	[((y) * img->line_length) + (img->bits_per_pixel >> 3) * (x)]) \
	= color;
}

static inline void	put_square(unsigned int color, t_image *img, \
								unsigned int x, unsigned int y)
{
	quick_put_pix(color, img, x * 4, y * 4);
	quick_put_pix(color, img, x * 4 + 1, y * 4);
	quick_put_pix(color, img, x * 4 + 2, y * 4);
	quick_put_pix(color, img, x * 4 + 3, y * 4);
	quick_put_pix(color, img, x * 4, y * 4 + 1);
	quick_put_pix(color, img, x * 4 + 1, y * 4 + 1);
	quick_put_pix(color, img, x * 4 + 2, y * 4 + 1);
	quick_put_pix(color, img, x * 4 + 3, y * 4 + 1);
	quick_put_pix(color, img, x * 4, y * 4 + 2);
	quick_put_pix(color, img, x * 4 + 1, y * 4 + 2);
	quick_put_pix(color, img, x * 4 + 2, y * 4 + 2);
	quick_put_pix(color, img, x * 4 + 3, y * 4 + 2);
	quick_put_pix(color, img, x * 4, y * 4 + 3);
	quick_put_pix(color, img, x * 4 + 1, y * 4 + 3);
	quick_put_pix(color, img, x * 4 + 2, y * 4 + 3);
	quick_put_pix(color, img, x * 4 + 3, y * 4 + 3);
}

t_image	*upscale(t_image *dest, t_image *src)
{
	unsigned int	x;
	unsigned int	y;
	char			*src_addr;

	src_addr = src->addr;
	y = 0;
	while (y < (unsigned int)src->size.y)
	{
		x = 0;
		while (x < (unsigned int)src->size.x)
		{
			put_square(*(unsigned int *)src_addr, dest, x, y);
			src_addr += src->bits_per_pixel >> 3;
			x++;
		}
		y++;
	}
	return (dest);
}
