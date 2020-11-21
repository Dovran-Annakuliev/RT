#include "../../includes/rtv1.h"

int		parse_type_light(char *line)
{
	int res = -1;
	char	**split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
	error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], "type:") != 0 ? error(WRONG_TYPE_LIGHT, line) : 0;
	if (ft_strcmp(split[1], "point") == 0)
		res = 2;
	else if (ft_strcmp(split[1], "sphere") == 0)
		res = 3;
	else if (ft_strcmp(split[1], "rectangle") == 0)
		res = 4;
	else
		error(WRONG_NAME_VALUE, line);
	free_split(&split);
	return (res);
}

static void read_size_object3d(int fd, t_rt *data)
{
	char *line;

	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				data->parse.obj3d_v_size++;
			}
			else if (line[1] == 'n' && line[2] == ' ')
			{
				data->parse.obj3d_vn_size++;
			}
		}
		else if (line[0] == 'f' && line[1] == ' ')
		{
			data->parse.obj_size++;
		}
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void read_object3d(int fd, t_rt *data)
{
	char *line;
	char *line_2;
	char **tmp;

	line_2 = NULL;
	get_next_line(fd, &line);
	tmp = ft_strsplit_space(line);
	if (ft_strcmp(tmp[0], "file") != 0)
		error(INVALID_ARGUMENTS_IN_LINE, line);
	if (((fd = open(line, O_RDONLY)) < 0) || ((read(fd, line_2, 0)) < 0))
		error(INVALID_ARGUMENTS, line);
	read_size_object3d(fd, data);
	ft_strdel(&line);
	ft_strdel(&line_2);
	close(fd);
}
