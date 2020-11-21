#include "../../includes/rtv1.h"

cl_float3	parse_object3d_vertex(char *line)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res.x = ft_atof(split[1]);
	res.x = ft_atof(split[2]);
	res.x = ft_atof(split[3]);
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
	res.x = ft_atof(split[2]);
	res.x = ft_atof(split[3]);
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
	res.x = data->parse.obj3d_v[ft_atoi(split[0])].x;
	res.y = data->parse.obj3d_v[ft_atoi(split[0])].y;
	res.z = data->parse.obj3d_v[ft_atoi(split[0])].z;
	res.s0 = data->parse.obj3d_vn[ft_atoi(split[normal_idx])].x;
	res.s1 = data->parse.obj3d_vn[ft_atoi(split[normal_idx])].y;
	res.s2 = data->parse.obj3d_vn[ft_atoi(split[normal_idx])].z;
	free_split(&split);
	return (res);
}

void 	parse_object3d_face(char *line, t_rt *data)
{
	cl_float3 res;
	char **split;
	cl_float8 tmp;
	float tmp_normal;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;

	tmp = parse_vertex_and_normal(split[1], data);
	data->parse.obj[data->parse.obj_index].tr_0 = (cl_float3){tmp.x, tmp.y, tmp.z};
	data->parse.obj[data->parse.obj_index].tr_normal = (cl_float3){tmp.s0, tmp.s1, tmp.s2};

	tmp = parse_vertex_and_normal(split[2], data);
	data->parse.obj[data->parse.obj_index].tr_1 = (cl_float3){tmp.x, tmp.y, tmp.z};
	if (data->parse.obj[data->parse.obj_index].tr_normal.x != tmp.s0
		|| data->parse.obj[data->parse.obj_index].tr_normal.y != tmp.s1
		|| data->parse.obj[data->parse.obj_index].tr_normal.z != tmp.s2)
		error(INVALID_ARGUMENTS_IN_LINE, line);

	tmp = parse_vertex_and_normal(split[3], data);
	data->parse.obj[data->parse.obj_index].tr_2 = (cl_float3){tmp.x, tmp.y, tmp.z};
	if (data->parse.obj[data->parse.obj_index].tr_normal.x != tmp.s0
		|| data->parse.obj[data->parse.obj_index].tr_normal.y != tmp.s1
		|| data->parse.obj[data->parse.obj_index].tr_normal.z != tmp.s2)
		error(INVALID_ARGUMENTS_IN_LINE, line);

	free_split(&split);
}
