/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:46:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/06/20 16:07:03 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

//populates the array of size 4 with four of t_point
//	index [0] is the right direction ->
//	index [1] is the down direction V
//	index [2] is the left direction <-
//	index [3] is the up direction ^
//The array needs to be allocated
void	ft_get_directions(t_point *directions)
{
	if (!directions)
		return ;
	directions[0] = point2(1, 0);
	directions[1] = point2(0, 1);
	directions[2] = point2(-1, 0);
	directions[3] = point2(0, -1);
}
