#include "../../includes/rtv1.h"

void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
	{
		e->key.keysym.sym == SDLK_a ? data->o[1].s_center.x-= 0.1 : 0;
		e->key.keysym.sym == SDLK_d ? data->o[1].s_center.x+= 0.1 : 0;
		e->key.keysym.sym == SDLK_w ? data->o[1].s_center.y-= 0.1 : 0;
		e->key.keysym.sym == SDLK_s ? data->o[1].s_center.y+= 0.1 : 0;
		e->key.keysym.sym == SDLK_r ? data->o[1].s_center.z+= 0.1 : 0;
		e->key.keysym.sym == SDLK_f ? data->o[1].s_center.z-= 0.1 : 0;
	}

}
