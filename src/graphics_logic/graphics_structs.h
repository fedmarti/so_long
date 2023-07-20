/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_structs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:54:06 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/20 16:51:26 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_STRUCTS_H
# define GRAPHICS_STRUCTS_H
# include "../t_point/point.h"

typedef struct s_img_fraction
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	offset;
	t_point	size;
	t_point	whole_image_size;
}	t_img_fraction;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	offset;
	t_point	size;
}	t_image;

typedef struct s_window {
	void	*win;
	t_point	size;
}	t_window;

#endif