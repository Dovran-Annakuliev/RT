#ifndef LIGHTS_H
#define LIGHTS_H

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>
#else
# include <GL/opengl.h>
# include <CL/opencl.h>
#endif

typedef struct		s_light
{
	int				type;
	cl_float3		pos;
	cl_float3		dir;
	float			intensity;
}					t_light;

t_light				new_ambient_light(float intensity);
t_light				new_point_light(cl_float3 pos, float intensity);
t_light				new_directional_light(cl_float3 dir, float intensity);



#endif
