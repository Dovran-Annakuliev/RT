#include "../includes/objects.h"


t_obj					new_sphere(cl_float3 center, cl_float radius, t_material material)
{
	t_obj		res;
	res.type = 0;
	res.s_center = center;
	res.s_radius = radius;
	res.material = material;
	return (res);
}

t_obj					new_plane(cl_float3 pos, cl_float3 normal, t_material material)
{
	t_obj	res;
	res.type  = 1;
	res.p_pos = pos;
	res.p_normal = normal;
	res.material = material;
	return (res);
}

t_obj					new_cone(cl_float3 pos, cl_float k, cl_float3 axis, t_material material)
{
	t_obj	res;
	res.type  = 2;
	res.cone_pos = pos;
	res.cone_angle = k;
	res.cone_axis= axis;
	res.material = material;
	return (res);
}
