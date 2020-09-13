#include "../../includes/rtv1.h"

void		mouse_controller(SDL_Event *e, t_rt *data)
{
	int x;
	int y;

	if (e && data)
		;
	SDL_GetMouseState(&x, &y);
//	ft_printf("x = %d, y = %d\n", x, y);
}
