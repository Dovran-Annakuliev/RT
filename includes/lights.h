#ifndef LIGHTS_H
#define LIGHTS_H

# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>

typedef struct		s_light
{
	cl_float3		pos;
	float			intensity;
}					t_light;

t_light			new_light_source(cl_float3 pos, float intensity);

#endif
