#include "../includes/rtv1.h"

void	error(int err)
{
	if (err == 1)
	{
		ft_printf("It's been fun. Don't come back.\n");
		exit(0);
	}
	else
	{
		ft_printf("%d\n", err);
		exit(0);
	}
}
