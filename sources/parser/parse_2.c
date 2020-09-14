#include "../../includes/rtv1.h"

void parse_material(int fd, t_obj *obj)
{
	char *line;

	get_next_line(fd, &line);
	ft_strdel(&line);

	get_next_line(fd, &line);
	obj->material.diff_color = parse_cl_float4(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line);

	ft_strdel(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line);
	ft_strdel(&line);
}
