#include "../../includes/rtv1.h"

static void check_type_obj(t_rt *data, char *line, t_material *material)
{
	if (line != NULL && line[0] == 'v' && line[1] == ' ')
	{
		data->parse.obj3d_v[data->parse.obj3d_v_idx] = parse_object3d_vertex(line);
		data->parse.obj3d_v_idx++;
	}
	else if (line != NULL && line[0] == 'f' && line[1] == ' ')
		parse_object3d_face(line, data, material);
}

void	parse_object3d_file(t_rt *data, char *source, t_material *material)
{
	int fd;
	char *line;
	char **split;

	line = NULL;
	split = ft_strsplit(source, '"');
	if (((fd = open(split[0], O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(INVALID_ARGUMENTS, split[0]);
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 0)
			check_type_obj(data, line, material);
		ft_strdel(&line);
	}
	free(line);
	close(fd);
}
