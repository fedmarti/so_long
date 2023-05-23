#define _XOPEN_SOURCE 500
#define _DEFAULT_SOURCE
#include <unistd.h>
#include "../so_long.h"
#include <stdio.h>
#include "../src/graphics_logic/graphics.h"
#include "../src/graphics_logic/graphics_internal.h"

void	setup_hooks(t_data *data);

//is called when you want to exit the program
//needs to be updated 
int	ft_quit(void *data)
{
	(void)data;
	exit(0);
}

t_vector	get_player_direction(t_input input)
{
	t_vector	direction;

	direction = vector2(input.right - input.left, input.down - input.up);
	if (direction.x && direction.y)
		direction = vector_normalize(direction);
	return (direction);
}

int	ft_process(void *data)
{
	// static t_point g_pos[1];
	// *g_pos = point_add(*g_pos, vector_to_point(vector_multiply(get_player_direction(((t_data *)data)->input), 10)));
	((t_data *)data)->pre_buffer = put_solid_color(((t_data *)data)->pre_buffer, 0x000000FF);
	blend_images(((t_data *)data)->buffer, ((t_data *)data)->pre_buffer, point2(0,0), overlay);
	mlx_put_image_to_window(((t_data *)data)->mlx, ((t_data *)data)->mlx_window, ((t_data *)data)->pre_buffer->img, 0, 0);
	usleep(10000);
	return (1);
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

int	main()
{
	t_data	*data;

	
	data = ft_calloc(1, sizeof(*data));
	if (!data)
		return (1);
	data = graphics_init(data);
	data->buffer = image_init_color(16, 16, ((t_data *)data)->mlx, 0x00FF0000);
	setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
}