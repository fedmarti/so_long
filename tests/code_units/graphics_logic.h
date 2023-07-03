#include "../../src/graphics_logic/graphics_structs.h"
#include "../raycaster/raycaster.h"

unsigned int	multiply(unsigned int dest_color, unsigned int src_color);
unsigned int	overlay(unsigned int dest_color, unsigned int src_color);
unsigned int	inverse(unsigned int dest_color, unsigned int src_color);
void			blend_images(t_image *src, t_image *dst, t_point position, \
				unsigned int (*blend_mode)(unsigned int, unsigned int));
t_data	*graphics_init(t_data *data);
void	img_free(t_image *img, void *mlx);
t_image	*upscale(t_image *dest, t_image *src);
t_image	*put_solid_color(t_image *dest, unsigned int color);
void	sprite_array_free(t_image **array, void *mlx);
t_image	*wrapper_init(unsigned int width, unsigned int height, void *mlx_img);
t_image	*image_init_color(unsigned int width, unsigned int height, \
						void *mlx, unsigned int color);
t_image	*image_init_xpm(t_image *dest_wrapper, char *filepath, void *mlx);

void	draw_line(t_image *img, t_point start, t_point end, unsigned int color);