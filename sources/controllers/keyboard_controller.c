#include "../../includes/rtv1.h"

void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
	{
		e->key.keysym.sym == SDLK_a ? data->camera.look_from.x += 0.2 : 0;
		e->key.keysym.sym == SDLK_d ? data->camera.look_from.x -= 0.2 : 0;
		e->key.keysym.sym == SDLK_w ? data->camera.look_from.y -= 0.2 : 0;
		e->key.keysym.sym == SDLK_s ? data->camera.look_from.y += 0.2 : 0;
		e->key.keysym.sym == SDLK_r ? data->camera.look_from.z += 0.2 : 0;
		e->key.keysym.sym == SDLK_f ? data->camera.look_from.z -= 0.2 : 0;
		update_camera(&data->camera);
	}

}
