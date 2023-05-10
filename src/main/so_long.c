/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/05/10 00:31:10 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../map_load/map_load.h"
#include <stdio.h>

void setup_hooks(t_data *data);

int	main(int argc, char **argv)
{
	t_data	*data;
	t_img	img;

	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (1);
	if (argc != 2)
	{
		printf("provide valid path as argument\n");
		return (1);
	}
	data->map = map_load(argv[1]);
	if (!data->map)
	{
		printf("%s map is invalid or failed to load\n", argv[1]);
		free(data);
		return (1);
	}
	for (int i = 0; data->map->map[i]; i++)
 		printf ("%s\n", data->map->map[i]);
	data->mlx = mlx_init();
	data->mlx_window = mlx_new_window(data->mlx, BASE_SCREEN_HEIGHT, BASE_SCREEN_WIDTH, NAME);
	img.img = mlx_xpm_file_to_image(data->mlx, "media/player/idle_front.xpm", &(img.size.x),  &(img.size.y));
	data->img = &img;
	setup_hooks(data);
	mlx_loop(data->mlx);
	map_free(&data->map);
	free(data);
}
