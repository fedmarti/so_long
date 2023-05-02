NAME = so_long

SRC = t_point/t_point.c \
	map_load/map_load.c \
	libft_plus/ft_do_nothing.c \
	libft_plus/ft_free_matrix.c
	libft_plus/ft_abs.c \
	libft_plus/ft_max.c \
	libft_plus/ft_min.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: libft get_next_line ${OBJS}
		@ gcc ${FLAGS} -o ${NAME} ${OBJS} /libft/libft.a ./get_next_line/gnl.a -lm
		@ echo "${NAME} created 🗿"

libft: 
		@ make -C /libft bonus

get_next_line:
		@ make -C ./get_next_line 

clean:
			@ rm -f *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) objs ✔️"

fclean:		clean
			@ rm -f ${NAME}
			@ echo "Deleting $(NAME) library ✔️"

re:			fclean all

.PHONY:		all clean fclean re