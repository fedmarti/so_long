NAME = raycast_test

LIB_DIR = ../code_units/

LIBRARIES = $(LIB_DIR)libgraphics.a \
	$(LIB_DIR)libinput.a \
	$(LIB_DIR)libpoint.a

LIBFT = $(LIBFT_DIR)libft.a

LIBFT_DIR = ../../libft/

MLX = $(MLX_DIR)libmlx.a

MLX_DIR = ../../minilibx-linux/

LINKER_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC = $(wildcard ./*.c)

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -g

.c.o:
	@ gcc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${LIBRARIES} ${LIBFT} ${MLX}
		@ gcc ${FLAGS} -o $@ $^ ${LINKER_FLAGS}
		@ echo "$@ created 🗿"

all: ${NAME}

$(LIBRARIES):
	@ make -sC $(LIB_DIR) $(@:$(LIB_DIR)%=%)

${MLX}: 
		@ make -s -C ../../minilibx-linux/

${LIBFT}:
		@ make -s -C ../../libft bonus clean

clean:
	@ rm -f *.o
	@ make -sC $(LIB_DIR) fclean
	
fclean:	clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re