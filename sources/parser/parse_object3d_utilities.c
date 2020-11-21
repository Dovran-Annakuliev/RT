#include "../../includes/rtv1.h"

cl_float3	parse_object3d_vertex(char *line)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	free_split(&split);
	return (res);
}

cl_float3	parse_object3d_normal(char *line)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	free_split(&split);
	return (res);
}

cl_float8 parse_vertex_and_normal(char *line, t_rt *data)
{
	char **split;
	int normal_idx;
	cl_float8 res;

	split = ft_strsplit(line, '/');
	if (ft_count_words_split((const char**)split) < 1
		|| ft_count_words_split((const char**)split) > 4)
		error(INVALID_ARGUMENTS_IN_LINE, line);
	normal_idx = ft_count_words_split((const char **)split);

	res.s0 = data->parse.obj3d_v[ft_atoi(split[0]) - 1].x;
	res.s1 = data->parse.obj3d_v[ft_atoi(split[0]) - 1].y;
	res.s2 = data->parse.obj3d_v[ft_atoi(split[0]) - 1].z;
	res.s3 = data->parse.obj3d_vn[ft_atoi(split[normal_idx - 1]) - 1].x;
	res.s4 = data->parse.obj3d_vn[ft_atoi(split[normal_idx - 1]) - 1].y;
	res.s5 = data->parse.obj3d_vn[ft_atoi(split[normal_idx - 1]) - 1].z;
	free_split(&split);
	return (res);
}

void 	parse_object3d_face(char *line, t_rt *data, t_material *material)
{
	char **split;
	cl_float8 tmp;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;

	data->parse.obj[data->parse.obj_index].type = 4;

	tmp = parse_vertex_and_normal(split[1], data);
	data->parse.obj[data->parse.obj_index].tr_0 = (cl_float3){tmp.s0, tmp.s1, tmp.s2};
	data->parse.obj[data->parse.obj_index].tr_normal = (cl_float3){tmp.s3, tmp.s4, tmp.s5};

	tmp = parse_vertex_and_normal(split[2], data);
	data->parse.obj[data->parse.obj_index].tr_1 = (cl_float3){tmp.s0, tmp.s1, tmp.s2};
	if (data->parse.obj[data->parse.obj_index].tr_normal.x != tmp.s3
		|| data->parse.obj[data->parse.obj_index].tr_normal.y != tmp.s4
		|| data->parse.obj[data->parse.obj_index].tr_normal.z != tmp.s5)
		error(INVALID_ARGUMENTS_IN_LINE, line);

	tmp = parse_vertex_and_normal(split[3], data);
	data->parse.obj[data->parse.obj_index].tr_2 = (cl_float3){tmp.s0, tmp.s1, tmp.s2};
	if (data->parse.obj[data->parse.obj_index].tr_normal.x != tmp.s3
		|| data->parse.obj[data->parse.obj_index].tr_normal.y != tmp.s4
		|| data->parse.obj[data->parse.obj_index].tr_normal.z != tmp.s5)
		error(INVALID_ARGUMENTS_IN_LINE, line);

	data->parse.obj[data->parse.obj_index].material.diff_color = material->diff_color;
	data->parse.obj[data->parse.obj_index].material.reflection = material->reflection;
	data->parse.obj[data->parse.obj_index].material.specular = material->specular;

	data->parse.obj_index++;
	free_split(&split);
}
