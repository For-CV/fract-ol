NAME = fractol
LIBFT_A = libft/libft.a
MLX_A = minilibx-linux/libmlx_Linux.a
SRC = fractol.c fractol_utils.c fractol_utils1.c fractol_init.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -O3 -Ilibft -Iminilibx-linux -Wno-incompatible-pointer-types

all: $(NAME)

$(NAME): $(LIBFT_A) $(MLX_A) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT_A):
	$(MAKE) bonus -C libft

$(MLX_A):
	$(MAKE) -C minilibx-linux

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C libft
	$(MAKE) clean -C minilibx-linux

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

.PHONY: all clean fclean re