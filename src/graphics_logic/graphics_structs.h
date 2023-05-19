/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_structs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 21:54:06 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 05:05:11 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_STRUCTS_H
# define GRAPHICS_STRUCTS_H
# include "../t_point/point.h"

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_point	size;
}	t_image;

typedef struct s_window {
	void	*win;
	t_point	size;
}	t_window;

#endif