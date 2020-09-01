#include "../includes/plane.h"

t_plane			new_plane(t_vector3 plane_origin, t_vector3 plane_normal)
{
	t_plane res;
	res.type  = 1;
	res.p_point = plane_origin;
	res.plane_normal = plane_normal;
	return (res);
}
