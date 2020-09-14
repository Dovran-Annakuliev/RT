#include "../includes/vectors.h"
#include <math.h>

cl_float3				new_vector3(float x, float y, float z)
{
	cl_float3 res;
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

cl_float3		vec_sub(cl_float3 v1, cl_float3 v2)
{
	cl_float3 res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

cl_float3		vec_cross(cl_float3 v1, cl_float3 v2)
{
	cl_float3 res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

cl_float3		vec_normalize(cl_float3 v)
{
	double l;

	l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (l >= .00001f)
	{
		return((cl_float3){v.x / l, v.y / l, v.z / l});
	}
	return (v);
}

cl_float3		mult_vec_scal(cl_float3 v, double s)
{
	cl_float3 res;

	res.x = v.x * s;
	res.y = v.y * s;
	res.z = v.z * s;
	return (res);
}
