#ifndef MATERIAL_H
# define MATERIAL_H

# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenCL/opencl.h>
# else
#  include <GL/gl.h>
#  include <CL/cl.h>
# endif

typedef struct	s_material
{
	cl_float4	diff_color;
	float		specular;
	float		reflection;
}				t_material;

#endif
