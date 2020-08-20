#include "../includes/rtv1.h"

void	error(int err)
{
	if (err == 1)
	{
		write(1, "It's been fun. Don't come back.\n", 32);
		exit(0);
	}
	else
	{
		ft_putnbr(err);
		exit(0);
	}
}
