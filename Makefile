NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../libft

SRCS = srcs/parse.c srcs/parse_utils.c raycasting/raycasting.c
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX = -lmlx -lXext -lX11 -lm #-Lmlx -lmlx -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
