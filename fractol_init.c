/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 15:00:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/14 15:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_set_val(int *val, char *arg, char *set)
{
	char	*trimmed;

	trimmed = ft_strtrim(arg, set);
	if (trimmed)
	{
		*val = ft_atoi(trimmed);
		free(trimmed);
	}
}

int	ft_parse_cl(char **argv, int argc, t_data *data)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_strnstr(argv[i], "WIDTH=", 6))
			ft_set_val(&data->width, argv[i], "WIDTH= ");
		else if (ft_strnstr(argv[i], "LENGTH=", 7))
			ft_set_val(&data->len, argv[i], "LENGTH= ");
		else if (ft_strnstr(argv[i], "I=", 2))
			ft_set_val(&data->index, argv[i], "I= ");
		i++;
	}
	return (0);
}

int	ft_load_mlx(char **argv, int argc, t_data *data)
{
	if (ft_parse_cl(argv, argc, data) || data->index <= 0)
		return (1);
	if (data->len <= 0 || data->width <= 0)
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

void	ft_create_palette(t_data *data)
{
	int	i;

	data->palette = malloc(sizeof(int) * data->index);
	if (!data->palette)
		ft_close(data, EXIT_FAILURE);
	i = 0;
	while (i < data->index)
	{
		data->palette[i] = (int)(sin(0.10 * i + 0) * 127 + 128) << 16
			| (int)(sin(0.10 * i + 2) * 127 + 128) << 8
			| (int)(sin(0.10 * i + 4) * 127 + 128);
		i++;
	}
}

void	ft_setup_mlx(t_data *data)
{
	data->win = mlx_new_window(data->mlx, data->width, data->len, "FRACTOL");
	if (!data->win)
		ft_close(data, EXIT_FAILURE);
	mlx_hook(data->win, KeyPress, KeyPressMask, ctlkey, (void *)data);
	mlx_hook(data->win, DestroyNotify, 0, ft_close, (void *)data);
	mlx_mouse_hook(data->win, ft_zoom, (void *)data);
	data->img = mlx_new_image(data->mlx, data->width, data->len);
	if (!data->img)
		ft_close(data, EXIT_FAILURE);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->e);
	if (!data->addr)
		ft_close(data, EXIT_FAILURE);
}
