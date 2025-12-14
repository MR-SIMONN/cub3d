NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
MLX = -lmlx -framework OpenGL -framework AppKit
SRCS        = cub3d.c utils/cleanup/cleanup.c parsing/cub3d_utils.c \
		parsing/mapcollecting.c parsing/map_collecting_utils.c \
		parsing/cub3d_utils2.c parsing/check_map.c \
		utils/get_next_line/get_next_line.c \
		utils/get_next_line/get_next_line_utils.c \
		utils/cleanup/trash_can.c \
		utils/cleanup/utils.c game/drawing.c \
		game/events.c game/game.c player_movement.c \
		game/render.c game/setup.c \
OBJS        = $(SRCS:.c=.o)

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

.PHONY: all clean fclean re