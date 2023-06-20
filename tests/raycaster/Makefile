NAME = raycast_test

LIBFT = ../../libft/libft.a


MLX = ../../minilibx-linux/libmlx.a

LINKER_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRC = $(wildcard ./*.c)

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	@ gcc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${LIBFT} ${OBJS} ${MLX}
		@ gcc ${FLAGS} -o $@ $^ ${LINKER_FLAGS}
		@ echo "$@ created 🗿"

all: ${NAME}

${MLX}: 
		@ make -s -C ../../minilibx-linux

${LIBFT}:
		@ make -s -C ../../libft bonus clean

clean:
	@ rm -f *.o
	
fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re