/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/03 19:31:23 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H
# include <math.h>

typedef struct s_point{
	int	x;
	int	y;
}	t_point;

//returns 0 if the two points equal each other, 1 if a is greater, else -1
int		vector_cmpr(t_point a, t_point b);
//pyhagora's theorem
double	vector_len(t_point	vector);
//returns t_point with x and why components
t_point	vector2(int x, int y);
//same thing as vector2 but it's malloc'd
t_point	*vector2_pointer(t_point vector2);
//vector math
t_point	vector_add(t_point	v1, t_point v2);

#endif
