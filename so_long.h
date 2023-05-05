/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:14:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/04 22:21:28 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft_plus/libft_plus.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
# include <stdlib.h>
# include "src/t_point/point.h"
# include "src/map_load/map_load.h"
# include "src/macro_headers/key_codes.h"

enum e_tile_type {
	Player = 'P',
	Wall = '#',
	Exit = 'E',
	Empty = ' ',
	Enemy = 'X',
	Collectable = 'C',
	Void = '\0'
};

enum e_enemy_type {
	Zombie = 1,
	Default = 0
};

typedef struct s_actor {
	void			*additional_stuct;
	t_point			position;
	t_point			velocity;
	unsigned int	height;
	unsigned int	width;
}	t_actor;

typedef struct s_enemy {
	enum e_enemy_type	type;	
}	t_enemy;

#endif
