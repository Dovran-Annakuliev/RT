#include "../../includes/rtv1.h"

void free_split(char **split)
{
//	for (int i = 0; split[i]; i++)
//		printf("split2[%d] = %s\n", i, split[i]);

	int i;

	i = -1;
	while (split[i++])
		ft_strdel(&split[i]);
	free(split);
	split = NULL;
}

float parse_float(char *line)
{
	float res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res = ft_atof(split[1]);

	free_split(split);
	return (res);
}

cl_float parse_cl_float(char *line)
{
	cl_float res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res = ft_atof(split[1]);

	free_split(split);
	return (res);
}

cl_float3 parse_cl_float3(char *line)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 4 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);

//	for (int i = 0; split[i]; i++)
//		ft_printf("split1[%d] = %s\n", i, split[i]);

	free_split(split);
//	for (int i = 0; split[i]; i++)
//		ft_printf("split1[%d] = %s\n", i, split[i]);
	return (res);
}

cl_float4 parse_cl_float4(char *line)
{
	cl_float4 res;
	char **split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 5 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	res.w = ft_atof(split[3]);

	free_split(split);
	return (res);
}
