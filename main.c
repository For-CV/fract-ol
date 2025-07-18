#include <stdio.h>

typedef	struct s_complex
{
	double	real;
	double	imaginary;
}	t_complex;

int	ft_mandelbrot(int x, int y)
{
	t_complex	z;
	t_complex	c;
	double	t;
	int	i = 0;

	z.real = 0;
	z.imaginary = 0;
	c.real = 2;
	c.imaginary = 5;
	while (i++ < 10)
	{ 
		t = (z.real * z.real) - (z.imaginary * z.imaginary);
		z.imaginary = 2 *  z.real * z.imaginary;
		z.real = t;
        z.real += c.real;
	    z.imaginary += c.imaginary;
        printf("i = %d, real = %f, imaginary = %f\n", i, z.real, z.imaginary);
	}
    x--;
    y--;
}

int main()
{
    ft_mandelbrot(0,0);
}