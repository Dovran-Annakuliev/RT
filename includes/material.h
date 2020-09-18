#ifndef MATERIAL_H
# define MATERIAL_H

# include <GL/gl.h>
# include <CL/cl.h>

typedef struct	s_material
{
	cl_float4	diff_color;
	float		specular;
	float		reflection;
}				t_material;

#endif
