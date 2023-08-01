/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/08/01 20:49:08 by fedmarti         ###   ########.fr       */
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

	if (argc != 2)
	{
		write(1, "provide valid path as argument\n", 31);
		return (1);
	}
	data = ft_calloc(1, sizeof(*data));
	data->state = InGame;
	if (!data)
		return (1);
	data = graphics_init(data);
	data->map = map_load(argv[1], data);
	if (!data->map)
	{
		write(1, argv[1], ft_strlen(argv[1]));
		write(1, " map is invalid or failed to load\n", 34);
		ft_quit(data);
	}
	setup_hooks(data);
	mlx_loop(data->mlx);
	ft_quit(data);
}
