/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/05/22 22:46:54 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../map_load/map_load.h"
#include <stdio.h>
#include "../graphics_logic/graphics.h"

void	setup_hooks(t_data *data);

void	*free_data(t_data *data)
{
	if (data->map)
		map_free(&data->map);
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

int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (1);
	if (argc != 2)
	{
		printf("provide valid path as argument\n");
		return (1);
	}
	data = graphics_init(data);
	data->map = map_load(argv[1], data);
	if (!data->map)
	{
		printf("%s map is invalid or failed to load\n", argv[1]);
		free(data);
		return (1);
	}
	for (int i = 0; data->map->map[i]; i++)
 		printf ("%s\n", data->map->map[i]);
	setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
}
