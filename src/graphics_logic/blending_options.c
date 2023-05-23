/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blending_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 23:55:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/23 10:36:05 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

// a color is stored as unsigned int like this 0xTTRRGGBB
// overlay() extracts the transparency byte by bitshifting to the right
// then choses to mix the two colors accordingly
// new = old * (1 - opacity) + front * opacity

unsigned int	overlay(unsigned int dest_color, unsigned int src_color)
{
	unsigned int	result;
	unsigned int	src_transp;
	// unsigned int	dst_transp;

	// dst_transp = get_transparency(dest_color);
	src_transp = get_transparency(src_color);
	result = multiply_colors(dest_color, src_transp, get_blue) \
	+ multiply_colors(src_color, 255 - src_transp, get_blue);
	result |= (multiply_colors(dest_color, src_transp << 8, get_green) \
	+ multiply_colors(src_color, (255 - src_transp) << 8, get_green)) << 8;
	result |= (multiply_colors(dest_color, src_transp << 16, get_red) \
	+ multiply_colors(src_color, (255 - src_transp) << 16, get_red)) << 16;
	// result |= src_transp * (src_transp <= dst_transp)  + dest_color * (dst_transp < src_transp);
	result |= isolate_transparency(dest_color);
	return (result);
}

//uses the second color as a mask, by extracting its transparency value
//according to which blends dest_color with its inverse
unsigned int	inverse(unsigned int dest_color, unsigned int mask)
{
	unsigned int	inverse;

	inverse = 0xFF - (get_blue(dest_color));
	inverse |= (0xFF - (get_green(dest_color))) << 8;
	inverse |= (0xFF - (get_red(dest_color))) << 16;
	inverse |= (isolate_transparency(mask));
	return (overlay(dest_color, inverse));
}

unsigned int	multiply(unsigned int dest_color, unsigned int src_color)
{
	unsigned int	result;

	result = multiply_colors(dest_color, src_color, get_blue);
	result |= multiply_colors(dest_color, src_color, get_green) << 8;
	result |= multiply_colors(dest_color, src_color, get_red) << 16;
	result |= isolate_transparency(dest_color);
	return (result);
}
