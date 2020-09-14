#include "../../includes/rtv1.h"

void parse_sphere(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 1;

	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].s_center = parse_cl_float3(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].s_radius = parse_cl_float(line);

	if (data->parse.obj[data->parse.obj_index].s_radius <= 0.f)
		error(WRONG_RADIUS, line);

	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);

	data->parse.obj_index++;
	ft_strdel(&line);
}

void parse_plane(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 2;

	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].p_pos = parse_cl_float3(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].p_normal = parse_cl_float3(line);

	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);

	data->parse.obj_index++;
	ft_strdel(&line);
}

void parce_ambient_light(int fd, t_rt *data)
{
	char *line;

	data->parse.light[data->parse.light_index].type = 1;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity = parse_float(line);

	if (data->parse.light[data->parse.light_index].intensity < 0.f
	        || data->parse.light[data->parse.light_index].intensity > 1.f)
		error(WRONG_INTENSITY, line);

	data->parse.light_index++;
	ft_strdel(&line);
}

void parce_point_light(int fd, t_rt *data)
{
	char *line;

	data->parse.light[data->parse.light_index].type = 2;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].pos = parse_cl_float3(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity = parse_float(line);

	if (data->parse.light[data->parse.light_index].intensity < 0.f
		|| data->parse.light[data->parse.light_index].intensity > 1.f)
		error(WRONG_INTENSITY, line);

	data->parse.light_index++;
	ft_strdel(&line);
}
void parce_directional_light(int fd, t_rt *data)
{
	char *line;

	data->parse.light[data->parse.light_index].type = 3;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].dir = parse_cl_float3(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity = parse_float(line);

	if (data->parse.light[data->parse.light_index].intensity < 0.f
		|| data->parse.light[data->parse.light_index].intensity > 1.f)
		error(WRONG_INTENSITY, line);

	data->parse.light_index++;
	ft_strdel(&line);
}
