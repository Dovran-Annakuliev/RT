#include "../../includes/rtv1.h"

void	parce_ambient_light(int fd, t_rt *data)
{
	char *line;

	data->parse.light[data->parse.light_index].type = 0;
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity =
			parse_float(line, "intensity");
	if (data->parse.light[data->parse.light_index].intensity < 0.f)
		error(WRONG_INTENSITY, line);
	data->parse.light_index++;
	ft_strdel(&line);
}

void	parce_directional_light(int fd, t_rt *data)
{
	char *line;

	data->parse.light[data->parse.light_index].type = 1;
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].dir =
			parse_cl_float3(line, "direction");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity =
			parse_float(line, "intensity");
	if (data->parse.light[data->parse.light_index].intensity < 0.f)
		error(WRONG_INTENSITY, line);
	data->parse.light_index++;
	ft_strdel(&line);
}

void	parce_point_light(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].type
			= parse_type_light(line);
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].pos =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].intensity =
			parse_float(line, "intensity");
	if (data->parse.light[data->parse.light_index].intensity < 0.f)
		error(WRONG_INTENSITY, line);
	ft_strdel(&line);
	if (data->parse.light[data->parse.light_index].type == 2)
		parse_light_point(fd, data);
	else if (data->parse.light[data->parse.light_index].type == 3)
		parse_light_sphere(fd, data);
	else if (data->parse.light[data->parse.light_index].type == 4)
		parse_light_rect(fd, data);
	data->parse.light_index++;
}
