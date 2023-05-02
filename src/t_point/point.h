/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/02 23:39:31 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H
# include <math.h>

typedef struct s_point{
	int	x;
	int	y;
}	t_point;


int		vector_cmpr(t_point a, t_point b);
double	vector_len(t_point	vector);
t_point	vector2(int x, int y);

#endif
