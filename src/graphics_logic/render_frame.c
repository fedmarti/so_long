/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:34:53 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 04:46:45 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "graphics.h"

t_image	*put_solid_color(t_image *dest, unsigned int color)
{
	char	*addr;
	int		i;

	i = 0;
	addr = dest->addr;
	while (i < dest->size.y * dest->size.x)
	{
		*(unsigned int *)addr = color;
		addr += dest->bits_per_pixel >> 3;
		i++;
	}
	return (dest);
}

void	render_frame(t_data *data)
{
	mlx_clear_window(data->mlx, data->mlx_window);
	data->pre_buffer = put_solid_color(data->pre_buffer, 0x0044FF00);
	data->buffer = put_solid_color(data->buffer, 0);
	data->buffer = upscale(data->buffer, data->pre_buffer);
	mlx_put_image_to_window \
	(data->mlx, data->mlx_window, data->buffer->img, 0, 0);
}
