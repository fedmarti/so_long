/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:52:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 04:42:55 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H


# include "../../minilibx-linux/mlx.h"
# include "graphics_structs.h"
# include "../../so_long.h"

void	render_frame(t_data *data);
t_data	*graphics_init(t_data *data);
void	free_img(t_image *img, void *mlx);
t_image	*upscale(t_image *dest, t_image *src);

#endif
