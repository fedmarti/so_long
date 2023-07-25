/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fedmarti <fedmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:48:45 by federico          #+#    #+#             */
/*   Updated: 2023/07/25 22:04:32 by fedmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "anime.h"
#include "../code_units/graphics_logic.h"
#include "../../src/animation_logic/animation.h"

void	*g_mlx = NULL;
void	*g_mlx_win = NULL;

void	blend_img_fraction(t_img_fraction *src, t_image *dst, t_point position, \
	unsigned int (*blend_mode)(unsigned int, unsigned int));

void	print_now(t_image	*img, t_point	pos){
	mlx_put_image_to_window(g_mlx, g_mlx_win, img->img, pos.x, pos.y);
}

void	put_fraction_now(t_img_fraction *img, t_point position)
{
	t_image *new = ft_calloc(1, sizeof(*new));
	t_image *big = ft_calloc(1, sizeof(*big));

	new->size = img->size;
	new->img = mlx_new_image(g_mlx, img->size.x, img->size.y);
	new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
	new->offset = (t_point){0,0};
	blend_img_fraction((img), new, (t_point){0,0}, overlay);
	big = image_init_color(new->size.x * 4, new->size.y * 4, g_mlx, 0);
	upscale(big, new);
	mlx_put_image_to_window(g_mlx, g_mlx_win, big->img, position.x * 4, position.y * 4);
	mlx_destroy_image(g_mlx, new->img);
	mlx_destroy_image(g_mlx, big->img);
	
	free(big);
	free(new);
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
	if (!data->anime)
		return 0;
	data->time = ft_calloc(1, sizeof(*data->time));
	if (!data->time)
		return 0;
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
					printf("	frame n. %i: img:%p duration: %li offset = (%i, %i)\n", j, frame.img->addr, frame.duration, frame.img->offset.x, frame.img->offset.y);
				}
			}
			printf("tot_duration = %li\ntype = %s\n\n", animation.tot_duration, (animation.type == 0)? "Default" : "Looping");
		}
		animation_play("run", data->anime, 50);
	}
	setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
}

