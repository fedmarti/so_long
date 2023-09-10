/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_images_flipped.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:39:31 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 18:16:36 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_structs.h"

struct s_d
{
	t_point	*position;
	t_point	*i;
	t_point	*overflow_offset;
	void	**src_pixel;
	void	**dest_pixel;
};

static inline void	vars_init(struct s_d data, \
t_image *src, t_image *dest)
{
	*data.position = point_add(*data.position, src->offset);
	*data.overflow_offset = (t_point){data.position->x * \
	-(data.position->x < 0), data.position->y * -(data.position->y < 0)};
	data.i->y = 0;
	*data.src_pixel = src->addr + (data.overflow_offset->y + 1) * \
	src->line_length - sizeof(unsigned int);
	*data.dest_pixel = dest->addr + (data.position->y * dest->line_length \
	+ data.position->x * (dest->bits_per_pixel >> 3));
}

void	blend_images_flipped_x(t_image *src, t_image *dest, t_point position, \
unsigned int (*blend)(unsigned int, unsigned int))
{
	t_point	i;
	t_point	overflow_offset;
	void	*src_pixel;
	void	*dest_pixel;

	vars_init((struct s_d){&position, &i, &overflow_offset, &src_pixel, \
	&dest_pixel}, src, dest);
	while (i.y + position.y < dest->size.y \
	&& i.y + overflow_offset.y < src->size.y)
	{
		i.x = 0;
		while (i.x + position.x < dest->size.x \
		&& i.x + overflow_offset.x < src->size.x)
		{
			*(unsigned int *)dest_pixel = blend(*(unsigned int *)dest_pixel, \
			*(unsigned int *)src_pixel);
			dest_pixel += sizeof(unsigned int);
			src_pixel -= sizeof(unsigned int);
			i.x++;
		}
		dest_pixel += dest->line_length - (i.x * sizeof(unsigned int));
		src_pixel += src->line_length + (i.x * sizeof(unsigned int));
		i.y++;
	}
}

void	blend_img_fraction_flipped_x(t_img_fraction *src, t_image *dest, \
t_point position, unsigned int (*blend)(unsigned int, unsigned int))
{
	t_image	mock;

	mock = (t_image){(void *)0, src->addr, src->bits_per_pixel, \
	src->line_length, src->endian, src->offset, src->size};
	blend_images_flipped_x(&mock, dest, position, blend);
}
// typedef struct s_image {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// 	t_point	offset;
// 	t_point	size;
// }	t_image;