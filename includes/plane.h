#ifndef PLANE_H
#define PLANE_H

#include "vectors.h"

typedef struct	s_plane
{
	int			type;
	t_vector3	p_point;
	t_vector3	plane_normal;
}				t_plane;

t_plane			new_plane(t_vector3 plane_origin, t_vector3 plane_normal);

#endif
