#include "../../includes/rtv1.h"

void parse_material(int fd, t_obj *obj)
{
	char *line;

	get_next_line(fd, &line);
	free(&line);

	get_next_line(fd, &line);
	obj->material.diff_color = parse_cl_float4(line);

	free(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line);

	free(&line);
	get_next_line(fd, &line);
	obj->material.specular = parse_float(line);
	free(&line);
}
