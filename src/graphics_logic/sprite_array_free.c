/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_array_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:03:52 by fedmarti          #+#    #+#             */
/*   Updated: 2023/05/22 23:09:19 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	sprite_array_free(t_image **array, void *mlx)
{
	int	len;

	len = 0;
	while ((*array)[len].img)
		len++;
	while (len--)
	{
		mlx_destroy_image(mlx, (*array)[len].img);
	}
	free(*array);
	*array = NULL;
}
