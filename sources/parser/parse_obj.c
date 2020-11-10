#include "../../includes/rtv1.h"

void	parse_sphere(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 0;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].s_center =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].s_radius =
			parse_cl_float(line, "radius");
	if (data->parse.obj[data->parse.obj_index].s_radius <= 0.f)
		error(WRONG_RADIUS, line);
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_plane(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 1;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].p_pos =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].p_normal =
			parse_cl_float3(line, "normal");
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_cone(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 2;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cone_pos =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cone_angle =
			parse_cl_float(line, "angle");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cone_axis =
			parse_cl_float3(line, "axis");
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_cylinder(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 3;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cyl_pos =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cyl_r =
			parse_cl_float(line, "radius");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].cyl_axis =
			vec_normalize(parse_cl_float3(line, "axis"));
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_triangle(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 4;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].tr_0 =
			parse_cl_float3(line, "vertex0");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].tr_1 =
			parse_cl_float3(line, "vertex1");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].tr_2 =
			parse_cl_float3(line, "vertex2");
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}
