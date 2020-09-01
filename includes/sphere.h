#ifndef SPHERE_H
#define SPHERE_H

#include "vectors.h"
#include "material.h"

typedef struct		s_sphere
{
	const char		*type;
	t_vector3		c;
	float			r;
	t_material		material;
}					t_sphere;

t_sphere			new_sphere(t_vector3 center, float radius, t_material);
#endif
