NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
SRCS        = cub3d.c ./cleanup/cleanup.c cub3d_utils.c mapcollecting.c map_collecting_utils.c cub3d_utils2.c check_map.c ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c
OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re