/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:52:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/25 18:06:56 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H


# include "../../minilibx-linux/mlx.h"
# include "graphics_structs.h"
# include "../../so_long.h"

void	put_pixel_to_img(t_image *img, int x, int y, int color);
void \
	draw_line_gba(t_image *img, t_point start, t_point end, unsigned int color);
void	render_game(t_data *data);
t_data	*graphics_init(t_data *data);
void	img_free(t_image *img, void *mlx);
t_image	*upscale(t_image *dest, t_image *src);
t_image	*put_solid_color(t_image *dest, unsigned int color);
void	sprite_array_free(t_image **array, void *mlx);
t_image	*wrapper_init(unsigned int width, unsigned int height, void *mlx_img);
t_image	*image_init_color(unsigned int width, unsigned int height, \
						void *mlx, unsigned int color);
t_image	*image_init_xpm(t_image *dest_wrapper, char *filepath, void *mlx);
t_image	*render_actors(t_data *data);
void	img_fraction_free(t_img_fraction *img);
#endif
