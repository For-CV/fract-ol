/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:00:07 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 19:10:03 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft/libft.h"
#include <stdio.h>

int	ft_zoom(int button, int x, int y, t_data *data)
{
	double	prev_zoom;
	double	mouse_r;
	double	mouse_i;

	if (!data)
		return (1);
	mouse_r = data->center_r - (x - (data->width >> 1))
		/ (data->zoom * (data->width >> 1));
	mouse_i = data->center_i - (y - (data->len >> 1))
		/ (data->zoom * (data->len >> 1));
	prev_zoom = data->zoom;
	if (button == 4)
		data->zoom *= 1.1;
	if (button == 5 && data->zoom > 1)
		data->zoom /= 1.1;
	if (data->zoom < 1)
		data->zoom = 1;
	data->center_r = mouse_r + (data->center_r - mouse_r)
		* (data->zoom / prev_zoom);
	data->center_i = mouse_i + (data->center_i - mouse_i)
		* (data->zoom / prev_zoom);
	ft_render(data);
	return (0);
}

int	ft_julia2(int x, int y, t_data *data)
{
	t_complex	z;
	double		temp;
	double		r2;
	double		i2;
	int			i;

	if (!data)
		return (1);
	i = 0;
	z.real = (x - (data->width >> 1)) / (data->zoom
			* (data->width >> 1)) + data->center_r;
	z.i = (y - (data->len >> 1))
		/ (data->zoom * (data->len >> 1)) + data->center_i;
	while (z.real * z.real + z.i * z.i <= 4 && i < data->index)
	{
		r2 = z.real * z.real;
		i2 = z.i * z.i;
		temp = z.real * (r2 - 3 * i2) + 0.400;
		z.i = z.i * (3 * r2 - i2);
		z.real = temp;
		i++;
	}
	if (i == data->index)
		my_mlx_pixel_put(data, x, y, 0x00000000);
	else
		my_mlx_pixel_put(data, x, y, ft_color(data, i));
	return (0);
}

int	ft_julia1(int x, int y, t_data *data)
{
	t_complex	z;
	double		temp;
	int			i;

	if (!data)
		return (1);
	i = 0;
	z.real = (x - (data->width >> 1)) / (data->zoom
			* (data->width >> 1)) + data->center_r;
	z.i = (y - (data->len >> 1)) / (data->zoom
			* (data->len >> 1)) + data->center_i;
	while (z.real * z.real + z.i * z.i <= 4 && i < data->index)
	{
		temp = z.real * z.real - z.i * z.i + 0.279;
		z.i = 2 * z.real * z.i;
		z.real = temp;
		i++;
	}
	if (i == data->index)
		my_mlx_pixel_put(data, x, y, 0x00000000);
	else
		my_mlx_pixel_put(data, x, y, ft_color(data, i));
	return (0);
}

void	ft_create_palette(t_data *data)
{
	int	i;
	int	r;
	int	g;
	int	b;

	data->palette = malloc(sizeof(int) * data->index);
	if (!data->palette)
		ft_close(data, EXIT_FAILURE);
	i = 0;
	while (i < data->index)
	{
		r = sin(0.10 * i + 0) * 127 + 128;
		g = sin(0.10 * i + 2) * 127 + 128;
		b = sin(0.10 * i + 4) * 127 + 128;
		data->palette[i] = (r << 16 | g << 8 | b);
		i++;
	}
}

int	ft_color(t_data *data, int i)
{
	if (i < 0 || i >= data->index)
		return (0x00000000);
	return (data->palette[i]);
}

// int ft_color_smooth(int i, double z_abs, int max_iter)
// {
//     // Aplica la fórmula de smooth coloring
//     double smooth_i = i + 1 - log(log(z_abs)) / log(2.0);

//     // Normaliza (0 a 1) para escalar colores y evitar overflow
//     double t = smooth_i / max_iter;
//     if (t > 1.0) t = 1.0; // Seguridad ante valores fuera de rango

//     // Ejemplo: gradiente arco iris (usa HSV->RGB si quieres más variedad)
//     int r = (int)(9 * (1 - t) * t * t * t * 255);
//     int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
//     int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

//     return (r << 16 | g << 8 | b);
// }

// ft_color_smooth(i, sqrt(z.real * 
// 			z.real + z.i * z.i), data->index) /
// 			 data->index << 0)

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2 || argc > 5)
	{
		write(2, ERR_MSSG, 70);
		return (1);
	}
	ft_init_data(&data);
	data.mlx = mlx_init();
	if (!data.mlx || ft_load_mlx(argv, argc, &data))
	{
		write(2, ERR_MSSG, 70);
		ft_close(&data, EXIT_FAILURE);
		return (1);
	}
	ft_create_palette(&data);
	data.win = mlx_new_window(data.mlx, data.width, data.len, "FRACTOL");
	if (!data.win)
	{
		write(2, ERR_MSSG, 70);
		ft_close(&data, EXIT_FAILURE);
		return (1);
	}
	mlx_hook(data.win, KeyPress, KeyPressMask, ctlkey, (void *)&data);
	mlx_hook(data.win, DestroyNotify, 0, ft_close, (void *)&data);
	mlx_mouse_hook(data.win, ft_zoom, (void *)&data);
	data.img = mlx_new_image(data.mlx, data.width, data.len);
	if (!data.img)
	{
		write(2, ERR_MSSG, 70);
		ft_close(&data, EXIT_FAILURE);
		return (1);
	}
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.e);
	if (!data.addr)
	{
		write(2, ERR_MSSG, 70);
		ft_close(&data, EXIT_FAILURE);
		return (1);
	}
	ft_render(&data);
	mlx_loop(data.mlx);
	return (0);
}
