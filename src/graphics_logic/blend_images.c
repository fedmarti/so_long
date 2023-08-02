/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:31:55 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:47:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_structs.h"
#include "blend_img_util.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);
void	*get_pixel(t_image *img, int x, int y);
int		get_pointer_offset_img(t_image *img, int x, int y);

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

void	blend_images(t_image *src, t_image *dst, t_point position, \
	unsigned int (*blend_mode)(unsigned int, unsigned int))
{
	t_point	i;
	t_point	offset;
	char	*dst_pixl;
	char	*src_pixl;

	if (!src || !dst || !src->addr || !dst->addr \
	|| position.x + src->size.x < 0 || position.y + src->size.y < 0)
		return ;
	src_pixl = vars_init((t_p){&i, &offset, src, dst, &position, &dst_pixl});
	while (position.y + i.y + offset.y < \
	dst->size.y && i.y + offset.y < src->size.y)
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
		next_line(&src_pixl, src, i.x);
		i.y++;
	}
}
