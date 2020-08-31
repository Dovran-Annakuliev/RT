#include "../includes/lights.h"


t_light			new_light_source(t_vector3 pos, float intensity)
{
	t_light	res;
	res.pos = pos;
	res.intensity = intensity;
	return (res);
}
