/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:19:39 by fedmarti          #+#    #+#             */
/*   Updated: 2023/08/01 22:58:00 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# ifndef TRANSPARENCY_MAX
#  define TRANSPARENCY_MAX 0xFF000000u
# endif

# ifndef RED_MAX
#  define RED_MAX 0x00FF0000u
# endif

# ifndef GREEN_MAX
#  define GREEN_MAX 0x0000FF00u
# endif

# ifndef BLUE_MAX
#  define BLUE_MAX 0x000000FFu
# endif

unsigned int	isolate_transparency(unsigned int color);
unsigned int	isolate_red(unsigned int color);
unsigned int	isolate_green(unsigned int color);
unsigned int	isolate_blue(unsigned int color);
unsigned int	get_transparency(unsigned int color);
unsigned int	get_red(unsigned int color);
unsigned int	get_green(unsigned int color);
unsigned int	get_blue(unsigned int color);
unsigned int	multiply_colors(unsigned int c1, unsigned int c2, \
unsigned int (*get_color)(unsigned int));

#endif