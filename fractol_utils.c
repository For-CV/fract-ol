/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:48:29 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/14 15:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_mandelbrot(t_data *data, int x, int y)
{
	int			i;
	t_complex	c;
	t_complex	z;
	double		temp;

	i = 0;
	c.real = (x - (data->width >> 1)) / (data->zoom
			* (data->width >> 1)) + data->center_r;
	c.i = (y - (data->len >> 1)) / (data->zoom
			* (data->len >> 1)) + data->center_i;
	z.real = 0;
	z.i = 0;
	while (z.real * z.real + z.i * z.i <= 4 && i < data->index)
	{
		temp = z.real * z.real - z.i * z.i + c.real;
		z.i = 2 * z.real * z.i + c.i;
		z.real = temp;
		i++;
	}
	if (i == data->index)
		my_mlx_pixel_put(data, x, y, 0x00000000);
	else
		my_mlx_pixel_put(data, x, y, ft_color(data, i));
	return (0);
}

int	ft_create_img(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->len)
		{
			if (data->set == 0)
				ft_mandelbrot(data, x, y);
			else if (data->set == 1)
				ft_julia1(x, y, data);
			else if (data->set == 2)
				ft_julia2(x, y, data);
			y++;
		}
		x++;
	}
	return (0);
}

void	ft_render(t_data *data)
{
	ft_create_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	ft_color(t_data *data, int i)
{
	if (i < 0 || i >= data->index)
		return (0x00000000);
	return (data->palette[i]);
}
