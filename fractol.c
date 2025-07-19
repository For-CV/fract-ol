#include "fractol.h"
#include "libft/libft.h"
#include <stdio.h>

int	ft_close(t_fractol *fractol)
{
	mlx_destroy_window(fractol -> mlx, fractol -> mlx_win);
	// mlx_destroy_image(fractol -> mlx, fractol -> img);
	mlx_destroy_display(fractol->mlx);
	free(fractol -> mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

void	my_mlx_pixel_put(t_fractol *fractol, int x, int y, int color)
{
	char	*dst;

	dst = fractol -> addr + (y * fractol -> line_length + x * (fractol -> bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_handler(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape || keysym == DestroyNotify)
		return (ft_close(fractol));
	return (0);
}

int	ft_zoom(int button, int x, int y, t_fractol *fractol)
{
	double prev_zoom;
	double mouse_r;
	double mouse_i;

	if (!fractol)
		return (1);
	mouse_r = fractol->center_r - (x - fractol->width / 2.0) / (0.5 * fractol->zoom * fractol->width);
	mouse_i = fractol->center_i - (y - fractol->length / 2.0) / (0.5 * fractol->zoom * fractol->length);
	prev_zoom = fractol->zoom;
	if (button == 4)
		fractol->zoom *= 1.1;
	if (button == 5 && fractol->zoom > 1)
		fractol->zoom /= 1.1;
	if (fractol->zoom < 1)
		fractol->zoom = 1;
	fractol->center_r = mouse_r + (fractol->center_r - mouse_r) * (fractol->zoom / prev_zoom);
	fractol->center_i = mouse_i + (fractol->center_i - mouse_i) * (fractol->zoom / prev_zoom);
	ft_create_img(fractol);
	mlx_put_image_to_window(fractol -> mlx, fractol -> mlx_win, fractol -> img, 0, 0);
	return (0);
}

int	ft_julia()
{
	// Implement Julia set logic here
	return (0);
}

int ft_color(int i)
{
	int r;
	int g;
	int b;
	
	r = sin(0.16 * i + 0) * 127 + 128;
	g = sin(0.16 * i + 2) * 127 + 128;
	b = sin(0.16 * i + 4) * 127 + 128;
	return (r << 16 | g << 8 | b);
}

// int ft_color_smooth(int i, double z_abs, int max_iter)
// {
//     // Aplica la fórmula de smooth coloring
//     double smooth_i = i + 1 - log(log(z_abs)) / log(2.0);

//     // Normaliza (0 a 1) para escalar colores y evitar overflow
//     double t = smooth_i / max_iter;
//     if (t > 1.0) t = 1.0; // Seguridad ante valores fuera de rango

//     // Ejemplo: gradiente arco iris (usa HSV -> RGB si quieres más variedad)
//     int r = (int)(9 * (1 - t) * t * t * t * 255);
//     int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
//     int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

//     return (r << 16 | g << 8 | b);
// }

// ft_color_smooth(i, sqrt(z.real * 
// 			z.real + z.imaginary * z.imaginary), fractol -> index) /
// 			 fractol->index << 0)

int	ft_mandelbrot(t_fractol *fractol, int x, int y)
{
	int	i;
	t_complex	c;
	t_complex	z;
	double temp;

	i = 0;
	c.real = (x - fractol -> width / 2.0) / (0.5 * fractol -> zoom * fractol -> width) + fractol -> center_r;
	c.imaginary = (y - fractol->length / 2.0) / (0.5 * fractol -> zoom * fractol -> length) + fractol -> center_i;
	z.real = 0;
	z.imaginary = 0;
	while (z.real * z.real + z.imaginary * z.imaginary <= 4 && i < fractol->index)
	{
		temp = z.real * z.real - z.imaginary * z.imaginary + c.real;
		z.imaginary = 2 * z.real * z.imaginary + c.imaginary;
		z.real = temp;
		i++;
	}
	if (i == fractol -> index)
		my_mlx_pixel_put(fractol, x, y, 0x00000000);
	else
		my_mlx_pixel_put(fractol, x, y, ft_color(i));
	return (0);
}

int	ft_create_img(t_fractol *fractol)
{
	int	x;
	int	y;

	if (!fractol)
		return (1);
	x = 0;
	while (x < fractol->width)
	{
		y = 0;
		while (y < fractol->length)
		{
			if (fractol -> set == 0)
				ft_mandelbrot(fractol, x, y);
			else if (fractol -> set == 1)
				ft_julia();
			y++;
		}
		x++;
	}
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

int	ft_load_mlx(char **argv, int argc, t_fractol *fractol)
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
		fractol -> index = ft_atoi(argv[i_pos]);
		free(argv[i_pos]);
		argv[i_pos] = NULL;
	}
	if (ft_find_in_matrix(argv, "julia", argc) > 0)
		fractol -> set = 1;
	else if (ft_find_in_matrix(argv, "mandelbrot", argc) > 0)
		fractol -> set = 0;
	else
		return (1);
	return (0);
}

void	ft_init_fractol(t_fractol *fractol)
{
	fractol->mlx = NULL;
	fractol->mlx_win = NULL;
	fractol->img = NULL;
	fractol->addr = NULL;
	fractol->bits_per_pixel = 0;
	fractol->line_length = 0;
	fractol->endian = 0;
	fractol->center_r = 0.0;
	fractol->center_i = 0.0;
	fractol->set = -1;
	fractol->width = 500;
	fractol->length = 500;
	fractol->index = 100;
	fractol->zoom = 1.0;
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2 || argc > 5)
		return (write(2, ERR_MSSG, 54), 1);
	ft_init_fractol(&fractol);
	if (ft_load_mlx(argv, argc, &fractol))
			return (write(2, ERR_MSSG, 54), 1);
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
    	return (1);
	fractol.mlx_win = mlx_new_window(fractol.mlx, fractol.width, fractol.length, "FRACT'OL");
	if (!fractol.mlx_win)
    	return (1);
	mlx_hook(fractol.mlx_win, KeyPress, KeyPressMask, key_handler, (void *)&fractol);
	mlx_hook(fractol.mlx_win, DestroyNotify, 0, ft_close, (void *)&fractol);
	mlx_mouse_hook(fractol.mlx_win, ft_zoom, (void *)&fractol);
	fractol.img = mlx_new_image(fractol.mlx, fractol.width, fractol.length);
	if (!fractol.img)
    	return (1);
	fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel, &fractol.line_length, &fractol.endian);
	if (!fractol.addr)
    	return (1);
	ft_create_img(&fractol);
	mlx_put_image_to_window(fractol.mlx, fractol.mlx_win, fractol.img, 0, 0);
	mlx_loop(fractol.mlx);
	return (0);
}