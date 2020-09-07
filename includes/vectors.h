#ifndef VECTORS_H
#define VECTORS_H

# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>

cl_float3				new_vector3(float x, float y, float z);
cl_float3				vec_sub(cl_float3 v1, cl_float3 v2);
cl_float3				vec_cross(cl_float3 v1, cl_float3 v2);
cl_float3				vec_normalize(cl_float3 v);
cl_float3				mult_vec_scal(cl_float3 v, double s);





#endif
