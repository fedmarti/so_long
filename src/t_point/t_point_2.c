/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_point_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 20:50:58 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/12 20:54:03 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_point_structs.h"

t_point	point_multiply(t_point point, int factor)
{
	t_point result;
	
	result.x = point.x * factor;
	result.y = point.y * factor;
	return (result);
}

t_point	point_divide(t_point point, int	divisor)
{
	t_point result;
	
	result.x = point.x / divisor;
	result.y = point.y / divisor;
	return (result);
}