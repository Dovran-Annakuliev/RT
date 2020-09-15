#include "../includes/rtv1.h"

void parse_error(int err, const char *message)
{
	if (err == INVALID_ARGUMENTS_IN_LINE)
		ft_printf("Invalid arguments in line: %s\n", message);
	else if (err == INVALID_ARGUMENTS)
		ft_printf("Invalid arguments: %s\n", message);
	else if (err == INVALID_TYPE)
		ft_printf("Invalid type in line: %s\n", message);
	else if (err == MISS_NEW_LINE)
		ft_printf("Miss new line in line: %s\n", message);
	else if (err == WRONG_FOV)
		ft_printf("Wrong angle in line: %s\n", message);
	else if (err == WRONG_RADIUS)
		ft_printf("Wrong radius in line: %s\n", message);
	else if (err == WRONG_REFLECTION)
		ft_printf("Wrong reflection in line: %s\n", message);
	else if (err == WRONG_INTENSITY)
		ft_printf("Wrong intensity in line: %s\n", message);
	else if (err == WRONG_NAME_VALUE)
		ft_printf("Wrong name value in line: %s\n", message);
	else if (err == WRONG_MATERIAL)
		ft_printf("Wrong material in line: %s\n", message);
}

void	error(int err, const char *message)
{
	if (err == 1)
		ft_printf("It's been fun. Don't come back.\n");
	else if (err <= INVALID_ARGUMENTS && err >= WRONG_MATERIAL)
		parse_error(err, message);
	else
		ft_printf("SDL init fail: %s[%d]\n", message, err);
	exit(0);
}
