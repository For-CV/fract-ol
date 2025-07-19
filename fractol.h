#ifndef FRACTOL_H
# define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>

#define	ERR_MSSG "fractol julia/mandelbrot\noptions:\nWIDTH={n}\n\
LENGTH={n}\nI={n}\n"

typedef	struct s_fractol
{
	void	*mlx_win;
	void	*mlx;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double		center_r;
	double		center_i;
	int	set;
	int	width;
	int	length;
	int	index;
	double		zoom;
}	t_fractol;

typedef	struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

int	ft_close(t_fractol *fractol);
void	my_mlx_pixel_put(t_fractol *fractol, int x, int y, int color);
int	key_handler(int keysym, t_fractol *fractol);
int	ft_zoom(int button, int x, int y, t_fractol *fractol);
int	ft_julia();
int	ft_mandelbrot(t_fractol *fractol, int x, int y);
int	ft_create_img(t_fractol *fractol);
int	ft_parse_cl(char **argv, int argc, t_fractol *fractol);
int	ft_load_mlx(char **argv, int argc, t_fractol *fractol);
int	ft_color(int i);

#endif