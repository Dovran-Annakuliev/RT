#include "../../includes/rtv1.h"

void	parse_light_point(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
			= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
	data->parse.light[data->parse.light_index].type = 2;
}

void	parse_light_sphere(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].r =
			parse_cl_float(line, "radius");
	if (data->parse.light[data->parse.light_index].r <= 0.f)
		error(WRONG_RADIUS, line);
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
		= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
	data->parse.light[data->parse.light_index].type = 3;
}

void	parse_light_rect(int fd, t_rt *data)
{
	char *line;

	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].width =
			parse_cl_float(line, "width");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].height =
			parse_cl_float(line, "height");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].normal =
			parse_cl_float3(line, "normal");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.light[data->parse.light_index].clr
			= parse_cl_float4(line, "color");
	clamp_color(&data->parse.light[data->parse.light_index].clr);
	ft_strdel(&line);
	data->parse.light[data->parse.light_index].type = 4;
}
