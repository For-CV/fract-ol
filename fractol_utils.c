/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rms35 <rms35@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:48:29 by rafael-m          #+#    #+#             */
/*   Updated: 2025/08/04 22:53:44 by rms35            ###   ########.fr       */
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

	if (!data)
		return (1);
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
			else
				return (1);
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

int	ft_parse_cl(char **argv, int argc, t_data *data)
{
	int		i;
	char	*trimmed;

	i = 1;
	while (i < argc)
	{
		if (ft_strnstr(argv[i], "WIDTH=", 6))
		{
			trimmed = ft_strtrim(argv[i], "WIDTH= ");
			data->width = ft_atoi(trimmed);
			free(trimmed);
		}
		else if (ft_strnstr(argv[i], "LENGTH=", 7))
		{
			trimmed = ft_strtrim(argv[i], "LENGTH= ");
			data->len = ft_atoi(trimmed);
			free(trimmed);
		}
		else if (ft_strnstr(argv[i], "I=", 2))
		{
			trimmed = ft_strtrim(argv[i], "I= ");
			data->index = ft_atoi(trimmed);
			free(trimmed);
		}
		i++;
	}
	return (0);
}

int	ft_load_mlx(char **argv, int argc, t_data *data)
{
	if (ft_parse_cl(argv, argc, data) || data->index == 0)
		return (1);
	if (data->len == 0 || data->width == 0)
		return (1);
	if (ft_find_in_matrix(argv, "julia1", 6) > 0)
		data->set = 1;
	else if (ft_find_in_matrix(argv, "mandelbrot", 10) > 0)
		data->set = 0;
	else if (ft_find_in_matrix(argv, "julia2", 6) > 0)
		data->set = 2;
	else
		return (1);
	return (0);
}

void	ft_init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->bpp = 0;
	data->line_len = 0;
	data->e = 0;
	data->center_r = 0.0;
	data->center_i = 0.0;
	data->set = -1;
	data->width = 500;
	data->len = 500;
	data->index = 100;
	data->zoom = 1.0;
	data->palette = NULL;
}
