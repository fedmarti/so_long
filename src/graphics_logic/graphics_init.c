/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 22:22:57 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 03:44:03 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx-linux/mlx.h"
#include "../../so_long.h"
#include "graphics_structs.h"

void	*free_data(t_data *data);

void	free_img(t_image *img, void *mlx)
{
	if (!img)
		return ;
	if (img->img && mlx)
	{
		mlx_destroy_image(mlx, img->img);
	}
	free(img);
}

static t_image	*buffer_init(unsigned int width, unsigned int height, void *mlx)
{
	t_image	*buffer;

	buffer = ft_calloc(1, sizeof(*buffer));
	if (!buffer)
		return (NULL);
	buffer->img = mlx_new_image(mlx, width, height);
	if (!buffer->img)
	{
		free(buffer);
		return (NULL);
	}
	buffer->addr = mlx_get_data_addr(buffer->img, &buffer->bits_per_pixel, \
	&buffer->line_length, &buffer->endian);
	if (!buffer->addr)
	{
		free_img(buffer, mlx);
		return (NULL);
	}
	buffer->size = point2((int)width, (int)height);
	return (buffer);
}

t_data	*graphics_init(t_data *data)
{	
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_data(data));
	data->mlx_window = mlx_new_window \
	(data->mlx, BASE_SCREEN_WIDTH * 4, BASE_SCREEN_HEIGHT * 4, NAME);
	if (!data->mlx_window)
		return (free_data(data));
	data->buffer = \
	buffer_init(BASE_SCREEN_WIDTH * 4, BASE_SCREEN_HEIGHT * 4, data->mlx);
	if (!data->buffer)
		return (free_data(data));
	data->pre_buffer = \
	buffer_init(BASE_SCREEN_WIDTH, BASE_SCREEN_HEIGHT, data->mlx);
	if (!data->pre_buffer)
		return (free_data(data));
	return (data);
}

// data->buffer->img = mlx_xpm_file_to_image
// (data->mlx, "media/player/idle_front.xpm", &(img.size.x),  &(img.size.y));