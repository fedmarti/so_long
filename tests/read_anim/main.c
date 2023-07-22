/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/07/22 17:10:40 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "anime.h"
#include "../code_units/graphics_logic.h"

void	*g_mlx = NULL;
void	*g_mlx_win = NULL;

void	print_now(t_image	*img, t_point	pos){
	mlx_put_image_to_window(g_mlx, g_mlx_win, img->img, pos.x, pos.y);
}

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

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
	{
		printf("%s [animation data file]\n", *argv);
		return (0);
	}
	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (1);
	data = graphics_init(data);
	g_mlx = data->mlx;
	g_mlx_win = data->mlx_window;
	data->anime = ft_calloc(1, sizeof(*data->anime));
	read_animation_file(argv[1], &data->anime, data->mlx);
	if (data->anime)
	{
		for (int i = 0; (size_t)i < data->anime->animations.n_members; i++)
		{
			t_animation animation = ((t_animation *)data->anime->animations.arr)[i];
			printf("animation name: %s\n", animation.name);
			if (animation.frames.arr)
			{
				for (int j = 0; (size_t)j < animation.frames.n_members; j++)
				{
					t_frame frame = ((t_frame *)animation.frames.arr)[j];
					printf("	frame n. %i: img:%p duration: %li\n", j, frame.img, frame.duration);
				}
			}
			printf("tot_duration = %li\ntype = %s\n\n", animation.tot_duration, (animation.type == 0)? "Default" : "Looping");
		}
	}
	setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
}

