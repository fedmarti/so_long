/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:55:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/22 20:13:07 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics_structs.h"

t_image	*put_solid_color(t_image *dest, unsigned int color)
{
	char	*addr;
	int		i;

	i = 0;
	addr = dest->addr;
	while (i < dest->size.y * dest->size.x)
	{
		*(unsigned int *)addr = color;
		addr += dest->bits_per_pixel >> 3;
		i++;
	}
	return (dest);
}

unsigned int	multiply_colors(unsigned int c1, unsigned int c2, \
unsigned int (*get_color)(unsigned int))
{
	return ((((get_color(c1) * get_color(c2)) + 511) >> 8) - 1);
}
