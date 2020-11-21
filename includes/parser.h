#ifndef PARSER_H
# define PARSER_H

typedef struct	s_parse
{
	t_obj		*obj;
	t_light		*light;
	t_camera	*camera;
	int			obj_size;
	int			light_size;
	int			camera_size;
	int			obj_index;
	int			light_index;
	int			camera_index;
	cl_float3	*obj3d_v;
	int 		obj3d_v_size;
	int 		obj3d_v_idx;
	cl_float3 	*obj3d_vn;
	int 		obj3d_vn_size;
	int 		obj3d_vn_idx;
}				t_parse;

#endif
