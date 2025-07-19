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
	int	set;
	int	width;
	int	length;
	int	index;
}	t_fractol;

typedef	struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		zoom;
}				t_data;

#endif