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
	int 			type_2;
	cl_float3		pos;
	cl_float3		dir;
	cl_float3		r;
	cl_float4		clr;
	cl_float3		width;
	cl_float3		height;
	cl_float3		normal;
	float			intensity;
}					t_light;

#endif
