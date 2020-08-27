#ifndef SPHERE_H
#define SPHERE_H

#include "vectors.h"

typedef struct		s_sphere
{
	t_vector3		c;
	float			r;
}					t_sphere;

t_sphere			new_sphere(t_vector3 center, float radius);
#endif
