#include "../includes/rtv1.h"

void	error(int err, const char *message)
{
	if (err == 1)
		ft_printf("It's been fun. Don't come back.\n");
	else
		ft_printf("SDL init fail: %s[%d]\n", message, err);
	exit(0);
}
