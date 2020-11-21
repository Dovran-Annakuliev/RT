#include "../../includes/rtv1.h"

void	parse_rectangle(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 5;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].rec_0 =
			parse_cl_float3(line, "vertex0");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].rec_1 =
			parse_cl_float3(line, "vertex1");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].rec_2 =
			parse_cl_float3(line, "vertex2");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].rec_3 =
			parse_cl_float3(line, "vertex3");
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_circle(int fd, t_rt *data)
{
	char *line;

	data->parse.obj[data->parse.obj_index].type = 6;
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].crcl_pos =
			parse_cl_float3(line, "position");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].crcl_normal =
			parse_cl_float3(line, "normal");
	ft_strdel(&line);
	get_next_line(fd, &line);
	data->parse.obj[data->parse.obj_index].crcl_r =
			parse_cl_float(line, "radius");
	if (data->parse.obj[data->parse.obj_index].s_radius <= 0.f)
		error(WRONG_RADIUS, line);
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}

void	parse_object3d(int fd, t_rt *data)
{
	char *line;
	char **split;

	data->parse.obj[data->parse.obj_index].type = 7;
	get_next_line(fd, &line);
	split = ft_strsplit_space(line);
	printf("line: %s/0\n", line);
	printf("file_line: %s/0\n", split[0]);
	printf("address_line: %s/0\n", split[1]);
	ft_count_words_split((const char**)split) != 2 ?
		error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	if (ft_strcmp(split[0], "file:") != 0)
		error(INVALID_ARGUMENTS_IN_LINE, line);
	parse_object3d_file(data, split[1]);
	ft_strdel(&line);
	parse_material(fd, &data->parse.obj[data->parse.obj_index]);
	data->parse.obj_index++;
	ft_strdel(&line);
}
