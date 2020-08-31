#include "../includes/sphere.h"

t_sphere		new_sphere(t_vector3 center, float radius, t_material material)
{
	t_sphere	res;
	res.c = center;
	res.r = radius;
	res.material = material;
	return (res);
}
