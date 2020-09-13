#include "../includes/lights.h"


t_light			new_ambient_light(float intensity)
{
	t_light	res;
	res.type = 1;
	res.intensity = intensity;
	return (res);
}

t_light			new_point_light(cl_float3 pos, float intensity)
{
	t_light	res;
	res.type = 2;
	res.pos = pos;
	res.intensity = intensity;
	return (res);
}

t_light			new_directional_light(cl_float3 dir, float intensity)
{
	t_light	res;
	res.type = 3;
	res.dir = dir;
	res.intensity = intensity;
	return (res);
}

