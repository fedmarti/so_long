/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 21:01:38 by fedmarti          #+#    #+#             */
/*   Updated: 2023/07/14 23:07:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H
# include "t_point_structs.h"


//returns 0 if the two points equal each other, 1 if a is greater, else -1
int			point_cmpr(t_point a, t_point b);
//pyhagora's theorem
double		point_len(t_point vector);
//returns t_point with x and y components
t_point		point2(int x, int y);
//same thing as point2 but it's malloc'd
t_point		*point2_pointer(t_point point2);
//vector addition but the x and y are only integers
t_point		point_add(t_point v1, t_point v2);
//vector subtraction but the x and y are only integers
t_point	point_subtract(t_point p1, t_point p2);
// it does what it says it does
// point.x *= factor
// point.y *= factor
t_point		point_multiply(t_point point, double factor);
// point.x /= divisor
// point.y /= divisor
t_point		point_divide(t_point point, int	divisor);
//returns t_vector with x and y components
t_vector	vector2(double x, double y);
//pyhagora's theorem
double		vector_len(t_vector vector);
//self explanatory
//returns the normalized vector
t_vector	vector_normalize(t_vector vector);
//v1.x + v2.x;
//v1.y + v2.y;
t_vector	vector_add(t_vector v1, t_vector v2);
//v1.x - v2.x;
//v1.y - v2.y;
t_vector	vector_subtract(t_vector v1, t_vector v2);
//multiplies each member by the given double
t_vector	vector_multiply(t_vector vector, double factor);
//divides each member by the given double
t_vector	vector_divide(t_vector vector, double divisor);
//subtracts v2 from v1 and then gets the length and rounds it to an int
//as a result if the vectors are aproximately the same it returns 0
int			vector_cmpr(t_vector v1, t_vector v2);
//rounds the (double) components of v to (int) and returns a t_point
t_point		vector_to_point(t_vector v);
//turns a t_point into a t_vector
t_vector	point_to_vector(t_point p);


void	ft_get_directions(t_point *directions);

#endif
