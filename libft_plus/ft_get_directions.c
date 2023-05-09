/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_directions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:46:00 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/09 19:56:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/t_point/point.h"

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
	directions[0] = vector2(1, 0);
	directions[1] = vector2(0, 1);
	directions[2] = vector2(-1, 0);
	directions[3] = vector2(0, -1);
}
