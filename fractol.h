/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 22:59:30 by rafael-m          #+#    #+#             */
/*   Updated: 2025/07/21 16:33:08 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft/libft.h"

# define ERR_MSSG "fractol julia/mandelbrot\noptions:\nWIDTH={n}\n\
len={n}\nI={n}\n"

typedef struct s_data
{
	void	*win;
	void	*mlx;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		e;
	double	center_r;
	double	center_i;
	int		set;
	int		width;
	int		len;
	int		index;
	double	zoom;
}	t_data;

typedef struct s_complex
{
	double	real;
	double	i;
}	t_complex;

int		ft_close(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ctlkey(int keysym, t_data *data);
int		ft_zoom(int button, int x, int y, t_data *data);
int		ft_julia1(int x, int y, t_data *data);
int		ft_julia2(int x, int y, t_data *data);
int		ft_mandelbrot(t_data *data, int x, int y);
int		ft_create_img(t_data *data);
int		ft_parse_cl(char **argv, int argc, t_data *data);
int		ft_load_mlx(char **argv, int argc, t_data *data);
int		ft_color(int i);
void	ft_init_data(t_data *data);
int		ft_load_mlx(char **argv, int argc, t_data *data);
int		ft_load_mlx(char **argv, int argc, t_data *data);
int		ft_load_mlx(char **argv, int argc, t_data *data);
int		ft_load_mlx(char **argv, int argc, t_data *data);

#endif
