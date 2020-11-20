#ifndef VECTORS_H
# define VECTORS_H

# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenCL/opencl.h>
# else
#  include <GL/gl.h>
#  include <CL/cl.h>
# endif

cl_float3				new_vector3(float x, float y, float z);
cl_float3				vec_add(cl_float3 v1, cl_float3 v2);
cl_float3				vec_sub(cl_float3 v1, cl_float3 v2);
cl_float3				vec_cross(cl_float3 v1, cl_float3 v2);
cl_float3				vec_normalize(cl_float3 v);
cl_float3				mult_vec_scal(cl_float3 v, double s);
cl_float				vec_dot(cl_float3 v1, cl_float3 v2);

#endif
