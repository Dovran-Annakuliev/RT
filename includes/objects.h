#ifndef OBJECTS_H
#define OBJECTS_H

# include "material.h"

typedef struct			s_obj
{
	int 				type;
	cl_float3			s_center;
	cl_float			s_radius;
	cl_float3			p_pos;
	cl_float3			p_normal;
	cl_float3			cone_pos;
	cl_float			cone_angle;
	cl_float3			cone_axis;
	t_material			material;
}						t_obj;


t_obj					new_sphere(cl_float3 center, cl_float radius, t_material material);
t_obj					new_plane(cl_float3 pos, cl_float3 normal, t_material material);
t_obj					new_cone(cl_float3 pos, cl_float radius, cl_float3 axis, t_material material);
#endif
