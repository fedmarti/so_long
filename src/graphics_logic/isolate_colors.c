/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:14:43 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 01:56:47 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

unsigned int	isolate_transparency(unsigned int color)
{
	return (color & TRANSPARENCY_MAX);
}

unsigned int	isolate_red(unsigned int color)
{
	return (color & RED_MAX);
}

unsigned int	isolate_green(unsigned int color)
{
	return (color & GREEN_MAX);
}

unsigned int	isolate_blue(unsigned int color)
{
	return (color & BLUE_MAX);
}
