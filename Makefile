NAME = so_long

LIBFT = libft/libft.a

MLX = minilibx-linux/libmlx.a

LINKER_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC = src/t_point/t_point.c \
	src/t_point/t_point_2.c \
	src/t_point/t_vector.c \
	src/t_point/t_vector_2.c \
	src/t_point/ft_get_directions.c \
	src/map_load/map_load.c \
	src/map_load/map_load_2.c \
	src/map_load/map_checks.c \
	src/map_load/map_checks_2.c \
	src/map_load/map_checks_3.c \
	src/map_load/map_actor_lists.c \
	src/player_controller/player_controller.c \
	src/player_controller/check_collisions_gba.c \
	src/player_controller/collision_types.c \
	src/player_controller/check_surrounding_area.c \
	src/player_controller/get_s_aabbs.c \
	src/player_controller/solve_s_aabbs.c \
	src/player_controller/swept_aabb.c \
	src/player_controller/util.c \
	src/player_controller/is_on_ground.c \
	src/main/so_long.c \
	src/main/ft_quit.c \
	src/main/setup_hooks.c \
	src/main/ft_process.c \
	src/handle_input/key_event.c \
	src/graphics_logic/graphics_init.c \
	src/graphics_logic/render_frame.c \
	src/graphics_logic/add_pixel.c \
	src/graphics_logic/color_utils.c \
	src/graphics_logic/isolate_colors.c \
	src/graphics_logic/get_color_channel.c \
	src/graphics_logic/blending_options.c \
	src/graphics_logic/blend_images.c \
	src/graphics_logic/blend_img_util.c \
	src/graphics_logic/upscale.c \
	src/graphics_logic/image_init.c \
	src/graphics_logic/render_actors.c \
	src/graphics_logic/blend_img_fraction.c \
	src/graphics_logic/blend_images_flipped.c \
	src/graphics_logic/sprite_array_free.c \
	src/graphics_logic/img_fraction_utils.c \
	src/graphics_logic/blend_img_fraction_util.c \
	src/actor_logic/actor_init.c \
	src/actor_logic/actor_logic.c  \
	src/actor_logic/enemy_init.c \
	src/actor_logic/exit_init.c \
	src/actor_logic/player_init.c \
	src/2d_geometry/raycast.c \
	src/2d_geometry/raycast_to_rectangle.c \
	src/2d_geometry/line_len.c \
	src/2d_geometry/line_in_area.c \
	src/2d_geometry/aabb.c \
	src/2d_geometry/generalized_bresenham_algorithm.c \
	src/time/time_update.c \
	src/time/lock_framerate.c \
	src/time/timeval_to_usec.c \
	src/time/time_subtract.c \
	src/time/time_recalibrate.c \
	src/animation_logic/new_animation.c \
	src/animation_logic/load_spritesheet.c \
	src/animation_logic/animation_load.c \
	src/animation_logic/render_animation.c \
	src/animation_logic/animation_play.c \
	src/animation_logic/animation_free.c \
	src/map/get_tile.c \
	src/counter/counter.c


OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	@ gcc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${LIBFT} ${MLX}
		@ gcc ${FLAGS} -o $@ $^ ${LINKER_FLAGS}
		@ echo "${NAME} created 🗿"

all: ${NAME}

${MLX}: 
		@ make -s -C ./minilibx-linux

${LIBFT}:
		@ make -s -C ./libft bonus clean

clean:
			@ rm -f *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) objs ✔️"

lclean:		clean
			@ rm -f ${NAME}
			@ echo "Deleting $(NAME) Binary ✔️"
			@ echo "Didn't remake Libft"


fclean:		clean
			@ rm -f ${NAME}
			@ make -s -C ./libft fclean
			@ echo "Deleting $(NAME) Binary ✔️"

re:			fclean all

lre:		lclean all
			

superclean: fclean
			@ make -s -C ./tests/read_anim fclean
			@ make -s -C ./tests/lin fclean
			@ make -s -C ./tests/raycaster fclean
			@ make -s -C ./tests/raycaster_square fclean
			@ make -s -C ./tests/raycaster_square_and_movement fclean
			@ make -s -C ./tests/raycaster_square_and_movement_2 fclean

.PHONY:		all clean fclean sclean re rre rrre
