/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 01:08:09 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 01:10:24 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_INTERNAL_H
# define GRAPHICS_INTERNAL_H

# include "graphics_structs.h"

unsigned int	multiply(unsigned int dest_color, unsigned int src_color);
unsigned int	overlay(unsigned int dest_color, unsigned int src_color);
unsigned int	inverse(unsigned int dest_color, unsigned int src_color);
void			blend_images(t_image *src, t_image *dst, t_point position, \
				unsigned int (*blend_mode)(unsigned int, unsigned int));


#endif
