/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/24 02:19:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "anime.h"
#include "../../src/animation_logic/animation.h"

#include "../code_units/graphics_logic.h"


void	blend_img_fraction(t_img_fraction *src, t_image *dst, t_point position, \
	unsigned int (*blend_mode)(unsigned int, unsigned int));


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
		blend_img_fraction((d->anime->sprites.arr) + i * d->anime->sprites.member_size, d->pre_buffer, pos, overlay);
		pos.y += ((t_img_fraction *)d->anime->sprites.arr)[i].size.y;
	}
	// blend_images(d->anime->spritesheet, d->pre_buffer, (t_point){32, 0}, overlay);
	blend_img_fraction(d->anime->current_frame, d->pre_buffer, (t_point){0, 0}, overlay);
	d->buffer = upscale(d->buffer, d->pre_buffer);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	usleep(16000);
	return (0);
}
