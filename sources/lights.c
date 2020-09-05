#include "../includes/lights.h"


t_light			new_light_source(cl_float3 pos, float intensity)
{
	t_light	res;
	res.pos = pos;
	res.intensity = intensity;
	return (res);
}
