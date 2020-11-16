#include "../../includes/rtv1.h"

float	parse_light_sphere(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].s_radius =
			parse_cl_float(line, "radius");
	if (data->parse.obj[data->parse.obj_index].s_radius <= 0.f)
		error(WRONG_RADIUS, line);
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
		= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
}

float	parse_light_point(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
			= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
}

float	parse_light_rect(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].dir =
			parse_cl_float(line, "width");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].dir =
			parse_cl_float(line, "height");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].dir =
			parse_cl_float3(line, "normal");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
			= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
}
