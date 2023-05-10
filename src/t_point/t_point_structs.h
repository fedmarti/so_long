/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point_structs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 02:21:21 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/10 02:22:01 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_POINT_STRUCTS_H
# define T_POINT_STRUCTS_H

//point in 2d space
//has an x and a y which are ints	
typedef struct s_point{
	int	x;
	int	y;
}	t_point;

//point or vector in 2d space
//has an x and a y which are doubles
typedef	struct s_vector
{
	double	x;
	double	y;
}	t_vector;

#endif