NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -fsanitize=address
MLX = -lmlx -framework OpenGL -framework AppKit
SRCS = cub3d.c \
        utils/cleanup/config_setup.c \
		utils/cleanup/destroy_tex.c \
        utils/cleanup/trash_can.c \
        utils/cleanup/utils.c \
        utils/get_next_line/get_next_line.c \
        utils/get_next_line/get_next_line_utils.c \
		parsing/cub3d_utils.c \
		parsing/map_collecting_parts/mapcollecting.c \
		parsing/map_collecting_parts/map_collecting_utils.c \
		parsing/map_collecting_parts/map_collecting_2.c \
		parsing/map_collecting_parts/map_collecting_3.c \
		parsing/map_collecting_parts/map_collecting_4.c \
		parsing/cub3d_utils2.c \
		parsing/check_map_parts/check_map_1.c \
		parsing/check_map_parts/check_map_2.c \
		parsing/check_map_parts/check_map_3.c \
		parsing/check_map_parts/check_map_4.c \
		parsing/check_map_parts/check_map_5.c \
        game/drawing.c \
        game/events.c \
        game/game.c \
        game/player_movement.c \
        game/render.c \
        game/setup.c \
		game/textures.c \
		game/texture_draw.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o : %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
