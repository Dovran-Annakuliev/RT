#include "../../includes/rtv1.h"

void parse_material(int fd, t_obj *obj)
{
	char *line;
	char **tmp;

	get_next_line(fd, &line);
	tmp = ft_strsplit_space(line);
	ft_strcmp(tmp[0], "material:") != 0 ? error(WRONG_MATERIAL, line) : 0;
	ft_strdel(&line);
	free_split(&tmp);

	get_next_line(fd, &line);
	obj->material.diff_color = parse_cl_float4(line, "color");
	clamp_color(&obj->material.diff_color);

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line, "specular");

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.reflection = parse_float(line, "reflection");

	if (obj->material.reflection < 0.f || obj->material.reflection > 1.f)
		error(WRONG_REFLECTION, line);

	ft_strdel(&line);
}

void parse_camera(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].look_from
		= parse_cl_float3(line, "look_from");

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].look_at
		= parse_cl_float3(line, "look_at");

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].vertical_fov
		= parse_float(line, "vertical_fov");

	if (data->parse.camera[data->parse.camera_index].vertical_fov > 90.f
		&& data->parse.camera[data->parse.camera_index].vertical_fov < 20.f)
		error(WRONG_FOV, line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].viewport_height
	= parse_float(line, "viewport_height");

	if (data->parse.camera[data->parse.camera_index].viewport_height > 10.f
		&& data->parse.camera[data->parse.camera_index].viewport_height < 2.f)
		error(WRONG_HEIGHT, line);

	data->parse.camera_index++;
	ft_strdel(&line);
}
