#include "../../includes/rtv1.h"

//totally bugged
//do not update camera if press key that are not camera controls
void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
	{
//		e->key.keysym.sym == SDLK_a ? data->camera.look_from.x += 0.2 : 0;
//		e->key.keysym.sym == SDLK_d ? data->camera.look_from.x -= 0.2 : 0;
//		e->key.keysym.sym == SDLK_w ? data->camera.look_from.y -= 0.2 : 0;
//		e->key.keysym.sym == SDLK_s ? data->camera.look_from.y += 0.2 : 0;
//		e->key.keysym.sym == SDLK_r ? data->camera.look_from.z += 0.2 : 0;
//		e->key.keysym.sym == SDLK_f ? data->camera.look_from.z -= 0.2 : 0;
		if (e->key.keysym.sym == SDLK_p)
		{
			data->samples = data->samples % 16 == 0 ? 1 : data->samples * 2;
			free(data->randoms);
			data->randoms = new_random_array(data->width, data->height, data->samples);
			printf("samples = %d\n", data->samples);
		}
		e->key.keysym.sym == SDLK_UP ? data->lights[1].pos.z-- : 0;
		e->key.keysym.sym == SDLK_DOWN ? data->lights[1].pos.z++ : 0;
		e->key.keysym.sym == SDLK_LEFT ? data->lights[1].pos.x-- : 0;
		e->key.keysym.sym == SDLK_RIGHT ? data->lights[1].pos.x++ : 0;
//		update_camera(&data->camera);
	}
}
