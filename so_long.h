/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:14:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:27:04 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft_plus/libft_plus.h"
# include "get_next_line/get_next_line_bonus.h"
# include <stdlib.h>
# include "src/t_point/point.h"

enum e_tile_type {
	Player = 'P',
	Wall = '#',
	Exit = 'E',
	Empty = ' ',
	Enemy = 'X',
	Collectable = 'C'
};

#endif