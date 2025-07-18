#include "fractol.h"
#include <stdio.h>
#define PI 3.14159265358979323846

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int	bytes_per_pixel;

	bytes_per_pixel = (data->bits_per_pixel / 8);
	dst = data->addr + (y * data->line_length + (x * bytes_per_pixel));
	*(unsigned int*)dst = color;
}

int	ft_close(t_fractol *fractol)
{
	mlx_destroy_window(fractol -> mlx, fractol -> mlx_win);
	// mlx_destroy_image(fractol -> mlx, fractol -> );
	mlx_destroy_display(fractol->mlx);
	free(fractol -> mlx);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_handler(int keysym, t_fractol *fractol)
{
	if (keysym == XK_Escape)
		return (ft_close(fractol));
	return (0);
}


int	ft_square(int x, int y, t_data img)
{
	int	i = 0;
	int	j;
	int	color;
	int	color2 = 0x0000FF00;
	int	color3;
	
	while (i < x)
	{
		j = 0;
		color = 0x000000FF;
		color3 = 0x00FF0000;
		while (j++ < y)
		{
			
			color3 -= 0x00010000;
			my_mlx_pixel_put(&img, j, i, color + color2 + color3);
		}
		color2 -= 0x00000100;
		i++;
	}
	return (0);
}

typedef	struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

// int	ft_mandelbrot(int x, int y, t_data img)
// {
// 	t_complex	z;
// 	t_complex	c;
// 	double	t;
// 	int	i = 0;

// 	z.real = 0;
// 	z.imaginary = 0;
// 	c.real = 2;
// 	c.imaginary = 5;
// 	while (i++ < 10)
// 	{ 
// 		t = (z.real * z.real) - (z.imaginary * z.imaginary);
// 		z.imaginary = 2 *  z.real * z.imaginary;
// 		z.real = t;
// 		z.real += c.real;
// 		z.imaginary += c.imaginary;
// 	}
// 	z.real += c.real;
// 	z.imaginary += c.imaginary;
// }
int	main(void)
{
	t_data img;
	int	x = 256;
	int	y = 256;
	t_fractol	fractol;

	fractol.mlx = mlx_init();
	fractol.mlx_win = mlx_new_window(fractol.mlx, 1920, 1080, "Prueba");
	mlx_hook(fractol.mlx_win, KeyPress, KeyPressMask, key_handler, (void *)&fractol);
	img.img = mlx_new_image(fractol.mlx, 256, 256);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	ft_square(x, y, img);
	mlx_put_image_to_window(fractol.mlx, fractol.mlx_win, img.img, 200, 200);
	mlx_put_image_to_window(fractol.mlx, fractol.mlx_win, img.img, 600, 200);
	mlx_string_put(fractol.mlx, fractol.mlx_win, 100, 100, 0x00FFFFFF, "SQUARE");
	mlx_loop(fractol.mlx);
}