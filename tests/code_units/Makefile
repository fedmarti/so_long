LIBFT = $(LIBFT_DIR)libft.a

LIBFT_DIR = ../../libft/
#
MLX = $(MLX_DIR)libmlx.a

MLX_DIR = ../../minilibx-linux/
#
LINKER_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
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

objects = $(patsubst %.c,%.o,$(call sources, $1))

all: ${POINT} ${GRAPHICS} ${PLAYER_CONTROLLER} ${INPUT} ${ACTOR_LOGIC} ${MAP_LOAD}

nothing:
	touch nothing

.c.o:
#	@ echo "compiling $< into $@"
	@ gcc ${FLAGS} -c $< -o $@

lib%.a:
	@ make -s ${call objects, $@}
	@ ar rc $@ ${call objects, $@}
#	@ echo "$@'s dir : { ${call directory, $@} }"
#	@ echo "$@'s sources : { ${call sources, $@} }"
#	@ echo "$@'s objects : { ${call objects, $@} }"
	@ echo "$@ archived :D"

${MLX}: 
		@ make -s -C $(MLX_DIR)

${LIBFT}:
		@ make -s -C $(LIBFT_DIR) bonus clean

clean:
			@ rm -f ${call objects, $(POINT)}
			@ rm -f ${call objects, ${GRAPHICS}}
			@ rm -f ${call objects, ${PLAYER_CONTROLLER}}
			@ rm -f ${call objects, ${INPUT}}
			@ rm -f ${call objects, ${ACTOR_LOGIC}}
			@ rm -f ${call objects, ${MAP_LOAD}}
			@ echo "Removed all objects files"

fclean:		clean
			@ rm -f ${POINT}
			@ rm -f ${GRAPHICS}
			@ rm -f ${PLAYER_CONTROLLER}
			@ rm -f ${INPUT}
			@ rm -f ${ACTOR_LOGIC}
			@ rm -f ${MAP_LOAD}
			@ echo "Removed all archives"

re:			fclean all

.PHONY:		all clean fclean re