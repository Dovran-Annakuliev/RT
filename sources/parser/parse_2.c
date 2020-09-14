#include "../../includes/rtv1.h"

void parse_material(int fd, t_obj *obj)
{
	char *line;

	get_next_line(fd, &line);
	ft_strdel(&line);

	get_next_line(fd, &line);
	obj->material.diff_color = parse_cl_float4(line);
	clamp_color(&obj->material.diff_color);

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.reflection = parse_float(line);

	if (obj->material.reflection < 0.f || obj->material.reflection > 1.f)
		error(WRONG_REFLECTION, line);

	ft_strdel(&line);
}

void parse_camera(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].look_from = parse_cl_float3(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.camera[data->parse.camera_index].look_at = parse_cl_float3(line);

	ft_strdel(&line);
	data->parse.camera[data->parse.camera_index].vertical_fov = parse_float(line);

	if (data->parse.camera[data->parse.camera_index].vertical_fov > 90.f
		&& data->parse.camera[data->parse.camera_index].vertical_fov < 20.f)
		error(WRONG_FOV, line);

	ft_strdel(&line);
	data->parse.camera[data->parse.camera_index].viewport_height = parse_float(line);

	if (data->parse.camera[data->parse.camera_index].viewport_height > 10.f
		&& data->parse.camera[data->parse.camera_index].viewport_height < 2.f)
		error(WRONG_HEIGHT, line);

	data->parse.obj_index++;
	ft_strdel(&line);
}
