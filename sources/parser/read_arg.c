#include "../../includes/rtv1.h"

void check_type(int fd, char *line, t_rt *data)
{
	if (ft_strcmp(line, "sphere:") == 0)
		parse_sphere(fd, line);
	else if (ft_strcmp(line, "plane:") == 0)
		parse_plane(fd, data);
	else if (ft_strcmp(line, "ambient_light:") == 0)
		parce_ambient_light(fd, data);
	else if (ft_strcmp(line, "point_light:") == 0)
		parce_point_light(fd, data);
	else if (ft_strcmp(line, "directional_light:") == 0)
		parce_directional_light(fd, data);
	else
		error(11, "lox");
}

static void	read_size(int fd, char *line, t_rt *data)
{
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "sphere:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "plane:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "ambient_light:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "point_light:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "directional_light:") == 0)
			data->parse.light_size++;
		free(line);
	}
}

void		read_arg(char *source, t_rt *data)
{
	char	*line;
	int		fd;

	line = NULL;
	if (((fd = open(source, O_RDONLY)) < 0)
		|| ((read(fd, line, 0)) < 0))
		error(INVALID_ARGUMENTS, "Bad_file");

	data->parse.obj_size = 0;
	data->parse.light_size = 0;
	data->parse.obj_index = 0;
	data->parse.light_index = 0;
	read_size(fd, line, data);
	data->parse.obj = (t_obj *)malloc(sizeof(t_obj) * data->parse.obj_size);
	data->parse.light = (t_light *)malloc(sizeof(t_light) * data->parse.light_size);

	close(fd);
	fd = open(source, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		check_type(fd, line, data);
		ft_strdel(&line);
	}
	free(line);
	close(fd);
}
