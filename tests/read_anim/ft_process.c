/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:13:50 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/22 16:19:52 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include "anime.h"
#include "../code_units/graphics_logic.h"

int	ft_process(void *data)
{
	t_data	*d = data;

	d->pre_buffer = put_solid_color(d->pre_buffer, 0xFF000000);
	if (d && d->anime && d->anime->spritesheet)
		blend_images(d->anime->spritesheet, d->pre_buffer, (t_point){0,0}, overlay);
	d->buffer = upscale(d->buffer, d->pre_buffer);
	mlx_put_image_to_window \
	(d->mlx, d->mlx_window, d->buffer->img, 0, 0);
	usleep(16000);
	return (0);
}
