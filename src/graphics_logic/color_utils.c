/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:55:13 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 01:56:34 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// inline unsigned int	subtract(unsigned int a, unsigned int b)
// {
// 	return (a - b);
// }

// inline unsigned int	add(unsigned int a, unsigned int b)
// {
// 	return (a + b);
// }

// inline unsigned int	multiply(unsigned int a, unsigned int b)
// {
// 	return (a * b);
// }

unsigned int	multiply_colors(unsigned int c1, unsigned int c2, \
unsigned int (*get_color)(unsigned int))
{
	return ((((get_color(c1) * get_color(c2)) + 511) >> 8) - 1);
}
