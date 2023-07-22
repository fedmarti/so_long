/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 20:14:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/21 23:52:41 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_structs.h"
#include "../../libft/libft.h"
#include "../../minilibx-linux/mlx.h"

t_image	*put_solid_color(t_image *dest, unsigned int color);

void	img_free(struct s_image *img, void *mlx)
{
	if (!img)
		return ;
	if (img->img && mlx)
	{
		mlx_destroy_image(mlx, img->img);
	}
	free(img);
}

//contrustcts t_image wrapper struct given width, height and void * to an img
t_image	*wrapper_init(unsigned int width, unsigned int height, void *mlx_img)
{
	t_image	*img;

	if (!mlx_img)
		return (NULL);
	img = ft_calloc(1, sizeof(*img));
	if (!img)
		return (NULL);
	img->img = mlx_img;
	img->size = point2((int) width, (int) height);
	img->addr = mlx_get_data_addr \
	(mlx_img, &img->bits_per_pixel, &img->line_length, &img->endian);
	return (img);
}

t_image	*image_init_color(unsigned int width, unsigned int height, \
						void *mlx, unsigned int color)
{
	t_image	*wrapper;
	void	*mlx_img;

	mlx_img = mlx_new_image(mlx, (int) width, (int) height);
	if (!mlx_img)
		return (NULL);
	wrapper = wrapper_init(width, height, mlx_img);
	if (!wrapper)
	{
		mlx_destroy_image(mlx, mlx_img);
		return (NULL);
	}
	wrapper = put_solid_color(wrapper, color);
	return (wrapper);
}

//the wrapper needs to be allocated already, usually as part of an array
//the function reads the file and fills the wrapper struct 
t_image	*image_init_xpm(t_image *dest_wrapper, char *filepath, void *mlx)
{
	if (!dest_wrapper)
		return (NULL);
	dest_wrapper->img = mlx_xpm_file_to_image \
	(mlx, filepath, &dest_wrapper->size.x, &dest_wrapper->size.y);
	if (!dest_wrapper->img)
	{
		img_free(dest_wrapper, mlx);
		return (NULL);
	}
	dest_wrapper->addr = mlx_get_data_addr(dest_wrapper->img, \
	&dest_wrapper->bits_per_pixel, &dest_wrapper->line_length, \
	&dest_wrapper->endian);
	return (dest_wrapper);
}
