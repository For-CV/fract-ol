#include "fractol.h"
#include <stdio.h>
#define PI 3.14159265358979323846
int	main(void)
{
	// void	*mlx;
	// void	*mlx_win;

	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	// mlx_loop(mlx);
    // mlx_win--;
	float t;
	t = sin(PI/2);
	printf("%f\n", t);
	printf("%lu\n", sizeof(PI));
	printf("%lu\n", sizeof(t));

}