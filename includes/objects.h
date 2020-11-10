#ifndef OBJECTS_H
# define OBJECTS_H

# include "material.h"

typedef struct			s_obj
{
	int					type;
	cl_float3			s_center;
	cl_float			s_radius;
	cl_float3			p_pos;
	cl_float3			p_normal;
	cl_float3			cone_pos;
	cl_float			cone_angle;
	cl_float3			cone_axis;
	cl_float3			cyl_pos;
	cl_float			cyl_r;
	cl_float3			cyl_axis;
	cl_float3			tr_0;
	cl_float3			tr_1;
	cl_float3			tr_2;
	t_material			material;
}						t_obj;

#endif
