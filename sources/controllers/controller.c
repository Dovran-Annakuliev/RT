#include "../../includes/rtv1.h"

void		controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
		keyboard_controller(e, data);
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
		mouse_controller(e, data);
}
