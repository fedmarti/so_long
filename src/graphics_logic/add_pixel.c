/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:51:52 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/17 23:33:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_structs.h"

int	get_pointer_offset_img(t_image *img, int x, int y)
{
	return (y * img->line_length + x * (img->bits_per_pixel >> 3));
}

void	*get_pixel(t_image *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr;
	if (!pixel)
		return ((void *)0);
	pixel += get_pointer_offset_img(img, x, y);
	return (pixel);
}

void	put_pixel_to_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = get_pixel(img, x, y);
	*(unsigned int *)dst = color;
}
