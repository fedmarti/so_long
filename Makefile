NAME = so_long

LIBFT = libft/libft.a

LIBFT_PLUS = libft_plus/libft_plus.a

MLX = minilibx-linux/libmlx.a

GET_NEXT_LINE = get_next_line/libgnl.a

LINKER_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC = src/t_point/t_point.c \
	src/t_point/t_vector.c \
	src/t_point/t_vector_2.c \
	src/map_load/map_load.c \
	src/map_load/map_checks.c \
	src/map_load/map_checks_2.c \
	src/map_load/map_actor_lists.c \
	src/main/so_long.c \
	src/main/ft_quit.c \
	src/main/setup_hooks.c \
	src/main/ft_process.c \
	src/handle_input/key_event.c \
	src/graphics_logic/render_frame.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	@ gcc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${LIBFT} ${LIBFT_PLUS} ${GET_NEXT_LINE} ${OBJS} ${MLX}
		@ gcc ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LIBFT_PLUS} ${GET_NEXT_LINE} ${LINKER_FLAGS}
		@ echo "${NAME} created 🗿"

all: ${NAME}

${MLX}: 
		@ make -s -C ./minilibx-linux

${LIBFT}:
		@ make -s -C ./libft bonus clean

${LIBFT_PLUS}:
		@ make -s -C ./libft_plus all clean	

${GET_NEXT_LINE}:
		@ make -s -C ./get_next_line all clean

clean:
			@ rm -f *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) objs ✔️"

fclean:		clean
			@ rm -f ${NAME}
			@ echo "Deleting $(NAME) Binary ✔️"

aclean:		fclean
			@ rm -f ${GET_NEXT_LINE} 
			@ rm -f ${LIBFT}
			@ rm -f ${LIBFT_PLUS}

sclean:		fclean
			@ make -s -C ./libft_plus fclean
			@ make -s -C ./get_next_line fclean
			@ make -s -C ./libft fclean

re:			fclean all

rre:		aclean all

rrre:		sclean all

.PHONY:		all clean fclean aclean sclean re rre rrre