NAME = test

LIBS = .../libft/libft.a 

SRC = main.c \
	../src/graphics_logic/blend_images.c \
	../src/graphics_logic/blending_options.c \
	../src/graphics_logic/color_utils.c \
	../src/graphics_logic/graphics_init.c \
	../src/graphics_logic/image_init.c \
	../src/graphics_logic/isolate_colors.c \
	../src/graphics_logic/get_color_channel.c \
	../src/t_point/t_point.c \
	../src/t_point/t_point_2.c \
	../src/t_point/t_vector.c \
	../src/t_point/t_vector_2.c \
	../src/main/setup_hooks.c  \
	../src/handle_input/key_event.c \
	../src/graphics_logic/add_pixel.c \


OBJ = $(SRC:.c=.o)

..c.o:
	gcc -g -c $< -o ${<:.c=.o}

${NAME}: ${OBJ} ${LIBS}
	gcc -g -L../minilibx-linux ${OBJ} ${LIBS} -o ${NAME}  -lm -lmlx -lXext -lX11 

all: ${NAME}

${LIBS}:
	@ make -s -C ../libft all clean

clean: 
	rm *.o -f

fclean: clean
	rm ${NAME} -f

re: fclean all

phony: clean fclean re