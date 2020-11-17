#ifndef LIGHTS_H
# define LIGHTS_H

# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenCL/opencl.h>
# else
#  include <GL/opengl.h>
#  include <CL/opencl.h>
# endif

typedef struct		s_light
{
	int				type;
	cl_float3		pos;
	cl_float3		dir;
	cl_float		r;
	cl_float4		clr;
	cl_float		width;
	cl_float		height;
	cl_float3		normal;
	float			intensity;
}					t_light;

#endif
