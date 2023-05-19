/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_channel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:19:19 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 01:53:02 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

unsigned int	get_transparency(unsigned int color)
{
	return (color >> 24);
}

unsigned int	get_red(unsigned int color)
{
	return (isolate_red(color) >> 16);
}

unsigned int	get_green(unsigned int color)
{
	return (isolate_green(color) >> 8);
}

unsigned int	get_blue(unsigned int color)
{
	return (isolate_blue(color));
}
