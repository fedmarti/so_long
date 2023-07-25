#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../../minilibx-linux/mlx.h"
# include "../../libft/libft.h"
# include "../../src/handle_input/input.h"
# include "../../src/macro_headers/key_codes.h"
# include <X11/X.h>
# include <stdlib.h>
# include "../../src/graphics_logic/graphics_structs.h"
# include "../../src/2d_geometry/line.h"
# include "../../src/2d_geometry/rectangle.h"
// # include "../../src/2d_geometry/raycast.h"

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*mlx_window;
// 	t_image	*buffer;
// 	t_image	*pre_buffer;
// 	t_input	input;
// 	t_list	*entity_list; 
// }	t_data;

// typedef struct s_hit
// {
// 	t_point	origin;
// 	t_point	intersection;	
// 	bool	collision;
// }	t_hit;

typedef struct s_hit t_hit;

struct s_hit	raycast(t_point p1, t_point p2, t_point p3, t_point p4);
struct s_hit	raycast_to_rectangle(t_point from, \
t_point to, t_point rec_pos, t_point rec_size);
bool			is_h2_closer(t_hit h1, t_hit h2);

enum	e_game_state {
	uselsess_shit_i_fucked_myself_by_coupling_graphics_with_this
};

typedef struct s_project_struct {
	t_point	position;
	// double	angle;
	t_point	mouse_position;
	t_list	*rec_list;
	t_rectangle square;
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



int		ft_quit(void *data);
int		ft_process(void *data);
int		on_click(int button, int x, int y, void *param);
void	setup_hooks(t_data *data);
void	player_controller(t_data *data);


#endif
