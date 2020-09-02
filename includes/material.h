#ifndef MATERIAL_H
#define MATERIAL_H

# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>

typedef struct	s_material
{
	cl_float4	diff_color;
}				t_material;

t_material		new_material(cl_float4 color);

#endif
