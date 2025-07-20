/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:48:29 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/20 22:49:51 by rafael-m         ###   ########.fr       */
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
	c.real = (x - data->width / 2.0) / (0.5
			* data->zoom * data->width) + data->center_r;
	c.i = (y - data->len / 2.0) / (0.5
			* data->zoom * data->len) + data->center_i;
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
		my_mlx_pixel_put(data, x, y, ft_color(i));
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

int	ft_parse_cl(char **argv, int argc, t_data *data)
{
	int	width_pos;
	int	len_pos;

	width_pos = ft_find_in_matrix(argv, "WIDTH=", argc);
	if (width_pos > 0)
	{
		argv[width_pos] = ft_strtrim(argv[width_pos], "WIDTH= ");
		if (!argv[width_pos])
			return (1);
		data->width = ft_atoi(argv[width_pos]);
		free(argv[width_pos]);
		argv[width_pos] = NULL;
	}
	len_pos = ft_find_in_matrix(argv, "len=", argc);
	if (len_pos > 0)
	{
		argv[len_pos] = ft_strtrim(argv[len_pos], "len= ");
		if (!argv[len_pos])
			return (1);
		data->len = ft_atoi(argv[len_pos]);
		free(argv[len_pos]);
		argv[len_pos] = NULL;
	}
	return (0);
}

int	ft_load_mlx(char **argv, int argc, t_data *data)
{
	int	i_pos;

	if (ft_parse_cl(argv, argc, data))
		return (1);
	i_pos = ft_find_in_matrix(argv, "I=", argc);
	if (i_pos > 0)
	{
		argv[i_pos] = ft_strtrim(argv[i_pos], "I= ");
		if (!argv[i_pos])
			return (1);
		data->index = ft_atoi(argv[i_pos]);
		free(argv[i_pos]);
		argv[i_pos] = NULL;
	}
	if (ft_find_in_matrix(argv, "julia1", argc) > 0)
		data->set = 1;
	else if (ft_find_in_matrix(argv, "mandelbrot", argc) > 0)
		data->set = 0;
	else if (ft_find_in_matrix(argv, "julia2", argc) > 0)
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
}
