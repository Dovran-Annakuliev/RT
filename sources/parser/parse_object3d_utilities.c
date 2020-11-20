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

cl_float4 parse_vertex_and_normal(char *line, t_rt *data)
{
	char **split;

	split = ft_strsplit(line, '/');
	if (ft_count_words_split((const char**)split) < 1
		|| ft_count_words_split((const char**)split) > 4)
		error(INVALID_ARGUMENTS_IN_LINE, line);

}

cl_float4	parse_object3d_face(char *line, t_rt *data)
{
	cl_float3 res;
	char **split;
	cl_float4 tmp;
	float tmp_normal;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;

	tmp = parse_vertex_and_normal(split[1], data);
	data->parse.obj[data->parse.obj_index].tr_0 = (cl_float3){tmp.x, tmp.y, tmp.z};
	tmp_normal = tmp.w;

	tmp = parse_vertex_and_normal(split[1], data);
	data->parse.obj[data->parse.obj_index].tr_0 = (cl_float3){tmp.x, tmp.y, tmp.z};

	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	res.w = ft_atof(split[4]);
	free_split(&split);
	return (res);
}
