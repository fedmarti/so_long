/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:53:08 by fedmarti          #+#    #+#             */
/*   Updated: 2023/09/08 23:18:11 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COUNTER_H
# define COUNTER_H

# include "../graphics_logic/graphics.h"
# define COUNTER_PATH "media/font/n0-9.xpm"

struct s_counter{
	double			distance_travelled;
	t_image			*sprite;
	t_image			*screen_space;
};

#endif