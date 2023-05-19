/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:14:56 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/19 04:28:29 by fedmarti         ###   ########.fr       */
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
# include "src/graphics_logic/graphics_structs.h"
# include "src/main/actor.h"
# ifndef NAME
#  define NAME "so_long"
# endif



typedef struct s_data
{
	t_map	*map;
	void	*mlx;
	void	*mlx_window;
	t_image	*buffer;
	t_image	*pre_buffer;
	t_input	input;
	//possibly more data
}	t_data;

int	ft_quit(void *data);
int	ft_process(void *data);

#endif
