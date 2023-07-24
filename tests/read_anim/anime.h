#ifndef ANIME_H
# define ANIME_H

# include "../../minilibx-linux/mlx.h"
# include "../../libft/libft.h"
# include "../../src/handle_input/input.h"
# include "../../src/macro_headers/key_codes.h"
# include <X11/X.h>
# include <stdlib.h>
# include "../../src/graphics_logic/graphics_structs.h"
# include "../../src/animation_logic/animation_structs.h"
#include "../../src/time/ft_time.h"

// typedef struct s_data
// {
// 	void	*mlx;
// 	void	*mlx_window;
// 	t_image	*buffer;
// 	t_image	*pre_buffer;
// 	t_input	input;
// 	t_list	*entity_list; 
// }	t_data;

enum	e_game_state {
	uselsess_shit_i_fucked_myself_by_coupling_graphics_with_this
};

typedef struct s_data
{
	t_anim_data			*anime;
	void				*mlx;
	void				*mlx_window;
	t_image				*buffer;
	t_image				*pre_buffer;
	t_input				input;
	enum e_game_state	state;
	struct s_time		*time;
}	t_data;


int		ft_quit(void *data);
int		ft_process(void *data);
int		on_click(int button, int x, int y, void *param);
void	setup_hooks(t_data *data);
void	read_animation_file(char *filepath, \
t_anim_data **anim_struct, void *mlx);


#endif