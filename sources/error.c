#include "../includes/rtv1.h"

void	error(int err, const char *message)
{
	if (err == 1)
		ft_printf("It's been fun. Don't come back.\n");
	else if (err == INVALID_ARGUMENTS_IN_LINE)
		ft_printf("Invalid arguments in line: %s\n", message);
	else if (err == INVALID_ARGUMENTS)
		ft_printf("Invalid arguments: %s\n", message);
	else if (err == INVALID_TYPE)
		ft_printf("Invalid type in line: %s\n", message);
	else
		ft_printf("SDL init fail: %s[%d]\n", message, err);
	exit(0);
}
