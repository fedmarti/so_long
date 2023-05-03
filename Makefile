NAME = so_long

LIBFT = libft/libft.a

LIBFT_PLUS = libft_plus/libft_plus.a

GET_NEXT_LINE = get_next_line/gnl.a

SRC = src/t_point/t_point.c \
	src/map_load/map_load.c \
	src/map_load/map_checks.c \
	src/map_load/map_actor_lists.c \
	src/main/so_long.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}
	@ echo "compiled $<"

${NAME}: ${LIBFT} ${LIBFT_PLUS} ${GET_NEXT_LINE} ${OBJS}
		@ gcc ${FLAGS} -o ${NAME} ${OBJS} ${LIBFT} ${LIBFT_PLUS} ${GET_NEXT_LINE} -lm
		@ echo "${NAME} created 🗿"

all: ${NAME}

${LIBFT}:
		@ make -C ./libft fclean bonus clean
		@ echo "compiled libft" 

${LIBFT_PLUS}:
		@ make -C ./libft_plus fclean all clean
		@ echo "compiled libft+"	

${GET_NEXT_LINE}:
		@ make -C ./get_next_line fclean all clean

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

re:			fclean all

rre:		aclean all

.PHONY:		all clean fclean aclean re