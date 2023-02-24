NAME	= cub3D
NAME_B	= cub3D_bonus

CC		= gcc
CFLAGS	= -g -Wall -Wextra -Werror
LXFLAGS		= -L$(MLX_PATH) -lmlx -lm -framework OpenGL -framework AppKit

MLX_PATH	= ./minilibx/
GNL_PATH	= ./get_next_line/

HEADER		= ./include/cub3D.h
HEADER_B	= ./include/cub3D_bonus.h
HEADER_GNL	= $(GNL_PATH)get_next_line.h
HEADER_MLX	= $(MLX_PATH)mlx.h

RM			= rm -f

SRCS_GNL	= get_next_line.c get_next_line_utils.c

FILES		= 0_cub3D 1_init	2_parsing	3_parsing	4_parsing\
				5_parsing 6_graphic	7_graphic	8_key	9_lists	10_str\

FILES_B		= 0_cub3D	1_init	2_parsing	3_parsing	4_parsing\
				5_parsing	6_parsing	7_graphic	8_graphic	9_graphic\
				10_key	11_key	12_minimap	13_doors	14_doors\
				15_mouse	16_lists	17_str\

SRCS		= $(addsuffix .c, $(FILES))
SRCS_B		= $(addsuffix _bonus.c, $(FILES_B))

SRCS		+= $(SRCS_GNL)
SRCS_B		+= $(SRCS_GNL)

SRC_DIR		= ./src/
SRC_B_DIR	= ./src_b/

vpath %.c $(SRC_DIR)
vpath %.c $(SRC_B_DIR)
vpath %.c $(GNL_PATH)

OBJS		= $(patsubst %.c, $(SRC_DIR)%.o, $(SRCS))

OBJS_B		= $(patsubst %.c, $(SRC_B_DIR)%.o, $(SRCS_B))

all:		$(NAME)

bonus:		$(NAME_B)

$(OBJS):	$(SRC_DIR)%.o: %.c $(HEADER) $(HEADER_GNL) $(HEADER_MLX)
			${CC} ${CFLAGS} -c $< -o $@

$(OBJS_B):	$(SRC_B_DIR)%.o: %.c $(HEADER_B) $(HEADER_GNL) $(HEADER_MLX)
			${CC} ${CFLAGS} -c $< -o $@

$(NAME): 	$(OBJS)
			$(MAKE) --directory=minilibx
			$(CC) $(OBJS) $(CFLAGS) $(LXFLAGS) -o $(NAME)
#			#$(MAKE) -C $(MLX_PATH)

$(NAME_B):	$(OBJS_B)
			$(MAKE) -C $(MLX_PATH)
			$(CC) $(OBJS_B) $(CFLAGS) $(LXFLAGS) -o $(NAME_B)

clean:		
			make clean -C $(MLX_PATH)
			${RM} ${OBJS} ${OBJS_B}

fclean: 	clean
			${RM} ${NAME} ${NAME_B}

mlx_re:		
			make re -C $(MLX_PATH) 

re:			fclean	all

.PHONY:		all clean fclean re