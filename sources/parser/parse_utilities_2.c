#include "../../includes/rtv1.h"

int		parse_type_light(char *line)
{
	int res = -1;
	char	**split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
	error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], "type:") != 0 ? error(WRONG_TYPE_LIGHT, line) : 0;
	if (ft_strcmp(split[1], "point") == 0)
		res = 2;
	else if (ft_strcmp(split[1], "sphere") == 0)
		res = 3;
	else if (ft_strcmp(split[1], "rectangle") == 0)
		res = 4;
	else
		error(WRONG_NAME_VALUE, line);
	free_split(&split);
	return (res);
}

static void read_size_object3d(int fd, t_rt *data)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
				data->parse.obj3d_v_size++;
			else if (line[1] == 'n' && line[2] == ' ')
				data->parse.obj3d_vn_size++;
		}
		else if (line[0] == 'f' && line[1] == ' ')
			data->parse.obj_size++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

static void	default_settings_parse(t_rt *data)
{
	data->parse.obj3d_v_size = 0;
	data->parse.obj3d_v_idx = 0;
	data->parse.obj3d_vn_size = 0;
	data->parse.obj3d_vn_idx = 0;
}

static void	parse_malloc(t_rt *data)
{
	data->parse.obj3d_v = (cl_float3*)malloc(sizeof(cl_float3)
											 * data->parse.obj3d_v_size);
	data->parse.obj3d_vn = (cl_float3*)malloc(sizeof(cl_float3)
											  * data->parse.obj3d_vn_size);
}

void read_object3d(int fd, t_rt *data)
{
	char *line;
	char *line_2;
	char **split;

	line_2 = NULL;
	get_next_line(fd, &line);
	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	if (ft_strcmp(split[0], "file:") != 0)
		error(INVALID_ARGUMENTS_IN_LINE, line);
	if (((fd = open(ft_strsplit(split[1], '"')[0], O_RDONLY)) < 0)
		|| ((read(fd, line_2, 0)) < 0))
			error(INVALID_ARGUMENTS, line);
	default_settings_parse(data);
	read_size_object3d(fd, data);
	parse_malloc(data);
	ft_strdel(&line);
	ft_strdel(&line_2);
	close(fd);
}
