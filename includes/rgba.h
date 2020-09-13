#ifndef RGBA_H
#define RGBA_H

typedef struct		u_rgba
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_rgba;

t_rgba				new_rgb_color(unsigned char r, unsigned char g,
									unsigned char b, unsigned char a);
#endif
