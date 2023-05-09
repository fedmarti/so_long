NAME = libft_plus.a

SRC = ft_abs.c \
	ft_do_nothing.c \
	ft_free_matrix.c \
	ft_get_next_direction.c \
	ft_get_directions.c \
	ft_lstlen.c \
	ft_max.c \
	ft_min.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	@ gcc ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
		@ ar rc -o ${NAME} ${OBJS} 
		@ echo "${NAME} created 🆗"

clean:
			@ rm -f *.o */*.o */*/*.o
			@ echo "Deleting $(NAME) objs ✔️"

fclean:		clean
			@ rm -f ${NAME}
			@ echo "Deleting $(NAME) library ✔️"

re:			fclean all

.PHONY:		all clean fclean re
