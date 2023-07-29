/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/06/23 23:12:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "raycaster.h"
#include "../code_units/graphics_logic.h"

void	*free_data(t_data *data)
{
	if (data->mlx)
	{
		if (data->mlx_window)
			mlx_destroy_window(data->mlx, data->mlx_window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
	return (NULL);
}

int	main(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (1);
	data = graphics_init(data);
	data->raycaster_struct = ft_calloc(1, sizeof(*data->raycaster_struct));
	setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
}
