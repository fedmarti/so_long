NAME = libft_plus.a

SRC = ft_abs.c \
	ft_sign.c \
	ft_do_nothing.c \
	ft_do_nothing_2.c \
	ft_free_matrix.c \
	ft_matrix_init.c \
	ft_get_next_direction.c \
	ft_get_directions.c \
	ft_lstlen.c \
	ft_max.c \
	ft_min.c \
	ft_clamp.c \
	ft_is_in_list.c \
	ft_lst_iteri_2.c \
	ft_lstclear_2.c \
	ft_lst_swap_next.c

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
