#include "../includes/vectors.h"

cl_float3	vec_add(cl_float3 v1, cl_float3 v2)
{
	cl_float3 res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}
