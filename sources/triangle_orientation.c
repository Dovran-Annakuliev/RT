#include "../includes/rtv1.h"

cl_int is_counter_clockwise(t_obj triangle, cl_float3 camera_dir)
{
	cl_float w;

	w = vec_dot(triangle.tr_normal, vec_sub(triangle.tr_0, camera_dir));
	return (w < 0);
}

void get_triangle_orientations(t_parse *p, cl_float3 camera_dir)
{
	int i;

	i = 0;
	while (i < p->obj_size)
	{
		if (p->obj[i].type == 4)
		{
			p->obj[i].tr_or = is_counter_clockwise(p->obj[i], camera_dir);
		}
		i++;
	}
}

void calculate_triangle_normals(t_parse *p)
{
	int i;

	i = 0;
	while (i < p->obj_size)
	{
		if (p->obj[i].type == 4)
		{
			p->obj[i].tr_normal = vec_normalize(vec_cross(vec_sub(p->obj[i].tr_1, p->obj[i].tr_0),
														  vec_sub(p->obj[i].tr_2, p->obj[i].tr_0)));
		}
		i++;
	}
}
