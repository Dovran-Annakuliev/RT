#include "../../includes/rtv1.h"

int		parse_type_light(char *line)
{
	int res = -1;
	char	**split;

	split = ft_strsplit_space(line);
	ft_count_words_split((const char**)split) != 2 ?
	error(INVALID_ARGUMENTS_IN_LINE, line) : 0;
	ft_strcmp(split[0], "type:") != 0 ? error(WRONG_NAME_VALUE, line) : 0;
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
