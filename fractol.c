/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:00:07 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/14 15:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_zoom(int button, int x, int y, t_data *data)
{
	double	prev_zoom;
	double	mouse_r;
	double	mouse_i;

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
	ft_setup_mlx(&data);
	ft_render(&data);
	mlx_loop(data.mlx);
	return (0);
}
