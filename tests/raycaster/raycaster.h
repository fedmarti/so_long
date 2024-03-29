#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../../minilibx-linux/mlx.h"
# include "../../libft/libft.h"
# include "../../src/handle_input/input.h"
# include "../../src/macro_headers/key_codes.h"
# include <X11/X.h>
# include <stdlib.h>
# include "../../src/graphics_logic/graphics_structs.h"

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*mlx_window;
// 	t_image	*buffer;
// 	t_image	*pre_buffer;
// 	t_input	input;
// 	t_list	*entity_list; 
// }	t_data;

typedef struct s_project_struct {
	t_point	position;
	// double	angle;
	t_point	mouse_position;
	t_list	*line_list;
}	rc_p_struct;

typedef struct s_data
{
	rc_p_struct			*raycaster_struct;
	void				*mlx;
	void				*mlx_window;
	t_image				*buffer;
	t_image				*pre_buffer;
	t_input				input;
	enum e_game_state	state;
}	t_data;

typedef struct s_line {
	t_point	start;
	t_point	end;
}	t_line;

int		ft_quit(void *data);
int		ft_process(void *data);
int		on_click(int button, int x, int y, void *param);
void	setup_hooks(t_data *data);


#endif