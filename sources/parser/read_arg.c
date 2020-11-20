#include "../../includes/rtv1.h"

static void	check_type(int fd, char *line, t_rt *data)
{
	if (ft_strcmp(line, "sphere:") == 0)
		parse_sphere(fd, data);
	else if (ft_strcmp(line, "plane:") == 0)
		parse_plane(fd, data);
	else if (ft_strcmp(line, "cone:") == 0)
		parse_cone(fd, data);
	else if (ft_strcmp(line, "cylinder:") == 0)
		parse_cylinder(fd, data);
	else if (ft_strcmp(line, "triangle:") == 0)
		parse_triangle(fd, data);
	else if (ft_strcmp(line, "rectangle:") == 0)
		parse_rectangle(fd, data);
	else if (ft_strcmp(line, "circle:") == 0)
		parse_circle(fd, data);
	else if (ft_strcmp(line, "object3d:") == 0)
		parse_object3d(fd, data);
	else if (ft_strcmp(line, "ambient_light:") == 0)
		parce_ambient_light(fd, data);
	else if (ft_strcmp(line, "point_light:") == 0)
		parce_point_light(fd, data);
	else if (ft_strcmp(line, "directional_light:") == 0)
		parce_directional_light(fd, data);
	else if (ft_strcmp(line, "camera:") == 0)
		parse_camera(fd, data);
	else
		error(INVALID_TYPE, line);
}

static void	read_size(int fd, char *line, t_rt *data)
{
	while (get_next_line(fd, &line))
	{
		if (ft_strcmp(line, "sphere:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "plane:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "cone:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "cylinder:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "triangle:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "rectangle:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "circle:") == 0)
			data->parse.obj_size++;
		else if (ft_strcmp(line, "object3d:") == 0)
			read_object3d(fd, data);
		else if (ft_strcmp(line, "ambient_light:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "point_light:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "directional_light:") == 0)
			data->parse.light_size++;
		else if (ft_strcmp(line, "camera:") == 0)
			data->parse.camera_size++;
		free(line);
	}
	if (data->parse.camera_size == 0)
		error(INVALID_CAMERA, "");
}

static void	default_settings_parse(t_rt *data)
{
	data->parse.obj_size = 0;
	data->parse.light_size = 0;
	data->parse.camera_size = 0;
	data->parse.obj_index = 0;
	data->parse.light_index = 0;
	data->parse.camera_index = 0;
}

static void	parse_malloc(t_rt *data)
{
	data->parse.obj = (t_obj *)malloc(sizeof(t_obj) * data->parse.obj_size);
	data->parse.light = (t_light *)malloc(sizeof(t_light)
			* data->parse.light_size);
	data->parse.camera = (t_camera *)malloc(sizeof(t_camera)
			* data->parse.camera_size);
}

void		read_arg(char *source, t_rt *data)
{
	char	*line;
	int		fd;

	line = NULL;
	if (((fd = open(source, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(INVALID_ARGUMENTS, source);
	default_settings_parse(data);
	parse_malloc(data);
	close(fd);
	fd = open(source, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 0)
		{
			check_type(fd, line, data);
			ft_strdel(&line);
		}
		else
			ft_strdel(&line);
	}
	free(line);
	close(fd);
}
