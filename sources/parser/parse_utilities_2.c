#include "../../includes/rtv1.h"

int		parse_type_light(char *line)
{
	float	res;
	char	**split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
	error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], "type:") != 0 ? error(WRONG_NAME_VALUE, line) : 0;
	if (ft_strcmp(split[1], "sphere"))
		res = 0;
	else if (ft_strcmp(split[1], "point"))
		res = 1;
	else if (ft_strcmp(split[1], "rectangle"))
		res = 2;
	else
		error(WRONG_NAME_VALUE, line);
	free_split(&split);
	return (res);
}
