/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/25 22:12:13 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "anime.h"
#include "../../src/animation_logic/animation.h"

#include "../code_units/graphics_logic.h"


void	put_fraction_now(t_img_fraction *img, t_point position);
void	put_pixel_to_img(t_image *img, int x, int y, int color);

void	blend_img_fraction(t_img_fraction *src, t_image *dst, t_point position, \
	unsigned int (*blend_mode)(unsigned int, unsigned int));

t_point	centered(t_img_fraction *src, t_image *dest)
{
	return ((t_point){(dest->size.x - src->size.x) / 2, (dest->size.y - src->size.y) / 2});
}


int	ft_process(void *data)
{
	t_data	*d = data;

	time_update(d->time);
	d->pre_buffer = put_solid_color(d->pre_buffer, 0xFF000000);
	// ft_putstr_fd("delta:", 1);
	// ft_putnbr_fd((int)d->time->delta, 1);
	// ft_putchar_fd('\n', 1);

	// ft_putchar_fd('\n', 1);
	if (d && d->anime)
		render_animation(d->anime, d->time->delta);
	t_point	pos = {16,0};
	for (int i = 0; (size_t)i < d->anime->sprites.n_members; i++)
	{
		// blend_img_fraction(((t_frame *)d->anime->current_animation.animation->frames.arr)[i].img, d->pre_buffer, (t_point){16, i * 16}, overlay);
		// blend_img_fraction((d->anime->sprites.arr) + i * d->anime->sprites.member_size, d->pre_buffer, pos, overlay);
		// put_fraction_now((d->anime->sprites.arr) + i * d->anime->sprites.member_size, pos);
		// usleep(500000);
		// put_pixel_to_img(d->pre_buffer, pos.x, pos.y, 0xFF0000);
		pos.y += ((t_img_fraction *)d->anime->sprites.arr)[i].size.y;
	}
	if (d->anime->current_frame){
	// blend_images(d->anime->spritesheet, d->pre_buffer, (t_point){32, 0}, overlay);
	if (d->flipped)
		blend_img_fraction_flipped_x(d->anime->current_frame, d->pre_buffer, centered(d->anime->current_frame, d->pre_buffer), overlay);
	else
		blend_img_fraction(d->anime->current_frame, d->pre_buffer, centered(d->anime->current_frame, d->pre_buffer), overlay);
	}
	d->buffer = upscale(d->buffer, d->pre_buffer);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	usleep(16000);
	return (0);
}
