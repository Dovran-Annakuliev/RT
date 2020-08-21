#include "../includes/rgba.h"

t_rgba		new_rgb_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	t_rgba new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	new_color.a = a;
	return (new_color);
}
