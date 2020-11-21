#include "../../includes/rtv1.h"

static void check_type_obj(t_rt *data, char *line){
	if (line != NULL && line[0] == 'v')
	{
		if (line[1] == ' ')
		{
			data->parse.obj3d_v[data->parse.obj3d_v_idx] = parse_object3d_vertex(line);
			data->parse.obj3d_v_idx++;
		}
		else if (line[1] == 'n')
		{
			data->parse.obj3d_vn[data->parse.obj3d_vn_idx] = parse_object3d_normal(line);
			data->parse.obj3d_vn_idx++;
		}
	}
	else if (line[0] == 'f')
		parse_object3d_face(line, data);
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


void	parse_object3d_file(t_rt *data, char *source)
{
	int fd;
	char *line;
	char **split;

	line = NULL;
	split = ft_strsplit(source, '"');
	if (((fd = open(split[0], O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(INVALID_ARGUMENTS, split[0]);
	default_settings_parse(data);
	parse_malloc(data);
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 0)
		{
			check_type_obj(data, line);
			ft_strdel(&line);
		}
		else
			ft_strdel(&line);
	}
	free(line);
	close(fd);
}
