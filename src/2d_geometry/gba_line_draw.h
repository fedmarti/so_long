/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gba_line_draw.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 00:44:24 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/30 00:51:42 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GBA_LINE_DRAW_H
# define GBA_LINE_DRAW_H

# include "../t_point/t_point_structs.h"

typedef struct s_generalized_bersenham_algorithm_data
{
	t_point	start;
	t_point	end;
	t_point	delta;
	t_point	sign;
	int		ex_change;
	int		e;
}	t_gba_data;

t_gba_data	gba_init(t_point start, t_point end);
t_point		gba_next(t_gba_data *d, t_point *current);

#endif