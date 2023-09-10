/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_fraction_util.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:24:33 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/10 18:41:08 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLEND_IMG_FRACTION_UTIL_H
# define BLEND_IMG_FRACTION_UTIL_H

# include "graphics_internal.h"
# include "colors.h"
# include "../t_point/point.h"

typedef struct s_pack
{
	t_point			*i;
	t_point			*offset;
	t_img_fraction	*src;
	t_image			*dst;
	t_point			*position;
	char			**dst_pixl;
}	t_p;

void	put_pixel_to_img(t_image *img, int x, int y, int color);
void	*get_pixel(t_image *img, int x, int y);
int		get_pointer_offset_img(t_image *img, int x, int y);
char	*vars_init_(t_p data);

#endif