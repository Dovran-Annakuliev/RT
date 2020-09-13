#include "../../includes/rtv1.h"

void free_split(char ***split)
{
	int i;

	i = 0;
	while (split[i])
		free(split[i]);
	free(split);
}

float parse_float(char *line)
{
	float res;
	char **split;

	split = ft_strsplit(line, ' ');
	res = ft_atof(split[1]);

	free_split(&split);
	return (res);
}

cl_float parse_cl_float(char *line)
{
	cl_float res;
	char **split;

	split = ft_strsplit(line, ' ');
	res = ft_atof(split[1]);

	free_split(&split);
	return (res);
}

cl_float3 parse_cl_float3(char *line)
{
	cl_float3 res;
	char **split;

	split = ft_strsplit(line, ' ');
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);

	free_split(&split);
	return (res);
}

cl_float4 parse_cl_float4(char *line)
{
	cl_float4 res;
	char **split;

	split = ft_strsplit(line, ' ');
	res.x = ft_atof(split[1]);
	res.y = ft_atof(split[2]);
	res.z = ft_atof(split[3]);
	res.w = ft_atof(split[3]);

	free_split(&split);
	return (res);
}
