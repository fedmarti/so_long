/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:52:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 18:07:05 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H


# include "../../minilibx-linux/mlx.h"
# include "graphics_structs.h"
# include "../../so_long.h"

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
#endif
