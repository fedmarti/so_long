LIBFT = ..libft/libft.a
#
LIBFT_PLUS = ..libft_plus/libft_plus.a
#
MLX = minilibx-linux/libmlx.a
#
GET_NEXT_LINE = get_next_line/libgnl.a
#
LINKER_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm
######
#
POINT = libpoint.a

POINT_DIR = ../../src/t_point
#
######
GRAPHICS = libgraphics.a

GRAPHICS_DIR = ../../src/graphics_logic
######
#
PLAYER_CONTROLLER = libplayer_controller.a

PLAYER_CONTROLLER_DIR = ../../src/player_controller
#
######
INPUT = libinput.a

INPUT_DIR = ../../src/handle_input
#######
#
ACTOR_LOGIC = libactor_logic.a

ACTOR_LOGIC_DIR= ../../src/actor_logic
#
#######
MAP_LOAD = libmap_load.a

MAP_LOAD_DIR = ../../src/map_load
#######
#
FLAGS = -Wall -Wextra -Werror -g

# uc = $(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$1))))))))))))))))))))))))))
# uc = $(shell echo $1 | tr '[:lower:]' '[:upper:]')
# turns shit uppercase

directory = $($(shell echo $(1:lib%.a=%) | tr '[:lower:]' '[:upper:]')_DIR)

sources = $(wildcard $(call directory, $1)/*.c)

objects = $(patsubst %.c, %.o, $(call sources, $1))

.c.o:
	@ gcc ${FLAGS} -c $< -o $@

all: ${POINT} ${GRAPHICS} ${PLAYER_CONTROLLER} ${INPUT} ${ACTOR_LOGIC} ${MAP_LOAD}

test:

lib%.a: ${call objects, $@}
	@ ar rc $@ $^
	@ echo "$@ archived :D"

${MLX}: 
		@ make -s -C ./minilibx-linux

${LIBFT}:
		@ make -s -C ./libft bonus clean

${LIBFT_PLUS}:
		@ make -s -C ./libft_plus all clean	

${GET_NEXT_LINE}:
		@ make -s -C ./get_next_line all clean

clean:
			@ rm -f ${call objects, $(POINT)}
			@ rm -f ${call objects, ${GRAPHICS}}
			@ rm -f ${call objects, ${PLAYER_CONTROLLER}}
			@ rm -f ${call objects, ${INPUT}}
			@ rm -f ${call objects, ${ACTOR_LOGIC}}
			@ rm -f ${call objects, ${MAP_LOAD}}

fclean:		clean
			@ rm -f ${POINT}
			@ rm -f ${GRAPHICS}
			@ rm -f ${PLAYER_CONTROLLER}
			@ rm -f ${INPUT}
			@ rm -f ${ACTOR_LOGIC}
			@ rm -f ${MAP_LOAD}

re:			fclean all

.PHONY:		all clean fclean 