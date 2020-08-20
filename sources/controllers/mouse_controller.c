#include "../../includes/rtv1.h"

void		mouse_controller(SDL_Event *e)
{
	int x;
	int y;

	if (e)
		;
	SDL_GetMouseState(&x, &y);
	ft_printf("x = %d, y = %d\n", x, y);
}
