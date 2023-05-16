/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:14:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/13 00:03:41 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "libft_plus/libft_plus.h"
# include "libft/libft.h"
# include "get_next_line/get_next_line_bonus.h"
// # include "src/graphics_logic/graphics.h"
# include "src/t_point/point.h"
# include "src/map_load/map_load.h"
# include "src/handle_input/input.h"
# include "src/macro_headers/key_codes.h"
# include "src/macro_headers/general_settings.h"
# include <X11/X.h>
# include <stdlib.h>

# ifndef NAME
#  define NAME "so_long"
# endif

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
	void				*additional_stuct;
	t_point				position;
	t_point				velocity;
	t_point				size;
	enum e_tile_type	type;
}	t_actor;

typedef struct s_enemy {
	enum e_enemy_type	type;	
}	t_enemy;

typedef struct s_img
{
	t_point	size;
	void	*img;
}	t_img;

typedef struct s_data
{
	t_map	*map;
	void	*mlx;
	void	*mlx_window;
	t_img	*img;
	t_point	pos;
	t_input	input;
	//possibly more data
}	t_data;

int	ft_quit(void *data);
int	ft_process(void *data);

#endif
