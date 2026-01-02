NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
MLX_DIR     = mlx_linux
MLX_LIB     = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
MLX_INC     = -I$(MLX_DIR)
SRCS        = cub3d.c \
              utils/cleanup/config_setup.c \
			  utils/cleanup/destroy_tex.c \
              utils/cleanup/trash_can.c \
              utils/cleanup/utils.c \
              utils/get_next_line/get_next_line.c \
              utils/get_next_line/get_next_line_utils.c \
              parsing/cub3d_utils.c \
              parsing/mapcollecting.c \
              parsing/map_collecting_utils.c \
              parsing/cub3d_utils2.c \
              parsing/check_map.c \
              game/drawing.c \
              game/events.c \
              game/game.c \
              game/player_movement.c \
              game/render.c \
              game/setup.c \
			  game/textures.c




OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re