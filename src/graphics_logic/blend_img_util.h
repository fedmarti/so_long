/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_img_util.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:37:11 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/02 00:43:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLEND_IMG_UTIL_H
# define BLEND_IMG_UTIL_H

# include "graphics_structs.h"
# include "../t_point/point.h"

typedef struct s_pack
{
	t_point	*i;
	t_point	*offset;
	t_image	*src;
	t_image	*dst;
	t_point	*position; 
	char	**dst_pixl;
}	t_p;

char	*vars_init(t_p data);

#endif