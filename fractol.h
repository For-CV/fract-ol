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
	int	i;
}	t_fractol;

typedef struct	s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

#endif