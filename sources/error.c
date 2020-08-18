#include "../includes/rtv1.h"

void	error(int err)
{
	if (err == 1)
	{
		write(1, "usage: ./fractol {fractal_type}\n", 32);
		write(1, "List of available fractals types:\n", 34);
		write(1, "1 - Mandelbrot\n", 15);
		write(1, "2 - Julia\n", 10);
		write(1, "3 - Burning Ship\n", 17);
		write(1, "4 - Bad Phoenix\n", 16);
		write(1, "5 - Classic Phoenix\n", 20);
		write(1, "6 - Special Mandelbrot Coloring\n", 33);
		write(1, "7 - Burning Julia\n", 18);
		write(1, "8 - Shattered Islands\n", 22);
		write(1, "9 - Tricorn\n", 12);
		write(1, "10 - Celestial_amoeba\n", 22);
		exit(0);
	}
	else
	{
		ft_putnbr(err);
		exit(0);
	}
}
