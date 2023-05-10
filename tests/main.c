#include "../minilibx-linux/mlx.h"
#include "../src/t_point/point.h"
#include <stdlib.h>
#include "../so_long.h"
#include "../src/macro_headers/key_codes.h"

//this contains the event code and their respective masks
#include <X11/X.h>


//               -L                          -lc
//			looks for library in       name of library which
//				  here                  it looks for (removing "lib-" prefix)
//					|                       |
//					V                       V
// g main.c -L../minilibx-linux           -lmlx -lXext -lX11 -o dio

// enum e_mlx_hooks{
// 	ON_KEYDOWN = 2,
// 	ON_KEYUP = 3,
// 	ON_MOUSEDOWN = 4,
// 	ON_MOUSEUP = 5,
// 	ON_MOUSEMOVE = 6,
// 	ON_EXPOSE = 12,
// 	ON_DESTROY = 17
// };


typedef	struct s_img
{
	t_point	size;
	void	*img;
}	t_img;




typedef struct s_data
{
	t_map	*map;
	void	*mlx;
	void	*mlx_window;
	t_img	*img;
	t_point	*pos;
	//possibly more data
} t_data;

int	free_all(t_data *data)
{
	if (!data)
		return (0);
	// if (data->map)
		// map_free(data->map);
	if (data->img->img)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->mlx_window)
		mlx_destroy_window(data->mlx, data->mlx_window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit (0);
	return (0);
}

int	print_key(int keypress, t_data *data)
{
	int unit = 5;
	(void *)data;
	switch (keypress)
	{
	case ESC_KEY:
	{
		printf("bye");
		free_all(data);
	}
	case ARROW_LEFT_KEY:
		if ((*data->pos).x >= unit)
			(*data->pos).x += -unit; 
		printf("<\n");
		break;
	case ARROW_UP_KEY:
		if ((*data->pos).y >= unit)
			(*data->pos).y += -unit; 
		printf("^\n");
		break;
	case ARROW_RIGHT_KEY:
		if ((*data->pos).x <= 600 - unit - data->img->size.x)
			(*data->pos).x += unit; 
		printf(">\n");
		break;
	case ARROW_DOWN_KEY:
		if ((*data->pos).y <= 600 - unit - data->img->size.y)
			(*data->pos).y += unit;
		printf("V\n");
		break;
	default:
		printf("pressed key: %i\n", keypress);
		break;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img->img, (*data->pos).x, (*data->pos).y);
	return (keypress);
}




t_data	*data_init(void)
{
	t_data	*data;

	data = calloc(sizeof(*data), 1);
	return (data);
}


int main()
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	
	t_point	position = {0,0};
	t_data	*data;

	data = data_init();
	if (!data)
		return (1);
	mlx = (void *)mlx_init();
	mlx_win = mlx_new_window(mlx, 600, 600, "Hello world!");
	img.img = mlx_xpm_file_to_image(mlx, "characters/slime.xpm", &(img.size.x),  &(img.size.y));
	if (!img.img)
		return (1);
	data->mlx = mlx;
	data->mlx_window = mlx_win;
	data->img = &img;
	data->pos = &position;
	mlx_put_image_to_window(mlx, mlx_win, img.img, position.x, position.y);
	mlx_hook(mlx_win, DestroyNotify, 0L, free_all, (void *)data);
	mlx_hook(mlx_win, KeyPress, KeyPressMask, print_key, (void *)data);
	
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);

} 