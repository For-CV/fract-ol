#include "fractol.h"
#include "libft/libft.h"
#include <stdio.h>

int	ft_close(t_fractol *fractol)
{
	mlx_destroy_window(fractol -> mlx, fractol -> mlx_win);
	// mlx_destroy_image(fractol -> mlx, fractol -> );
	mlx_destroy_display(fractol->mlx);
	free(fractol -> mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_handler(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		return (ft_close(fractol));
	return (0);
}

int	ft_parse_cl(char **argv, int argc, t_fractol *fractol)
{
	int	width_pos;
	int	length_pos;

	width_pos = ft_find_in_matrix(argv, "WIDTH=", argc);
	if (width_pos  > 0)
	{
		argv[width_pos] = ft_strtrim(argv[width_pos], "WIDTH= ");
		if (!argv[width_pos])
			return (1);
		fractol -> width = ft_atoi(argv[width_pos]);
		free(argv[width_pos]);
		argv[width_pos] = NULL;
	}
	length_pos = ft_find_in_matrix(argv, "LENGTH=", argc);
	if (length_pos  > 0)
	{
		argv[length_pos] = ft_strtrim(argv[length_pos], "LENGTH= ");
		if (!argv[length_pos])
			return (1);
		fractol -> length = ft_atoi(argv[length_pos]);
		free(argv[length_pos]);
		argv[length_pos] = NULL;
	}
	return (0);
}

int	ft_init_mlx(char **argv, int argc, t_fractol *fractol)
{
	int	i_pos;

	if (ft_parse_cl(argv, argc, fractol))
		return (1);
	i_pos = ft_find_in_matrix(argv, "I=", argc);
	if (i_pos  > 0)
	{
		argv[i_pos] = ft_strtrim(argv[i_pos], "I= ");
		if (!argv[i_pos])
			return (1);
		fractol -> i = ft_atoi(argv[i_pos]);
		free(argv[i_pos]);
		argv[i_pos] = NULL;
	}
	if (ft_find_in_matrix(argv, "julia", argc) > 0)
		fractol -> set = 1;
	else if (ft_find_in_matrix(argv, "mandelbrot", argc) > 0)
		fractol -> set = 0;
	else
		return (1);
	fractol -> mlx = mlx_init();
	fractol -> mlx_win = mlx_new_window(fractol -> mlx, fractol -> width, fractol -> length, "FRACT'OL");
	mlx_loop(fractol -> mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;
	// t_data	img;

	if (argc < 2 || argc > 5)
		return (write(2, ERR_MSSG, 54), 1);
	fractol.i = 100;
	fractol.width = 2048;
	fractol.length = 1252;
	if (ft_init_mlx(argv, argc, &fractol))
			return (write(2, ERR_MSSG, 54), 1);
	mlx_hook(fractol.mlx_win, KeyPress, KeyPressMask, key_handler, (void *)&fractol);
	// mlx_string_put(fractol.mlx, fractol.mlx_win, 750, 50, 0xFFFFFF, "FRACTOL");
	// mlx_hook(fractol.mlx_win, KeyPress, KeyPressMask, key_handler, (void *)&fractol);
	// mlx_loop(fractol.mlx);
	return (0);
}