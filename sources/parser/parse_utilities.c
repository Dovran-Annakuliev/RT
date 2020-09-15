#include "../../includes/rtv1.h"

void free_split(char ***split)
{
	int i;

	i = 0;
	while (((*split)[i]))
		ft_strdel(&((*split)[i++]));
	free(*split);
	*split = NULL;
}

float parse_float(char *line, char *type)
{
	float res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;

	ft_strcmp(split[0], type) != 0 ? error(WRONG_NAME_VALUE, line) : 0;

	res = ft_atof(split[1]);

	free_split(&split);

	return (res);
}

cl_float parse_cl_float(char *line, char *type)
{
	cl_float res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], type) != 0 ? error(WRONG_NAME_VALUE, line) : 0;
	res = ft_atof(split[1]);

	free_split(&split);

	return (res);
}

cl_float3 parse_cl_float3(char *line, char *type)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit_space(line);

	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], type) != 0 ? error(WRONG_NAME_VALUE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);

	free_split(&split);

	return (res);
}

cl_float4 parse_cl_float4(char *line, char *type)
{
	cl_float4 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 5 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], type) != 0 ? error(WRONG_NAME_VALUE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	res.w = ft_atof(split[3]);

	free_split(&split);

	return (res);
}
