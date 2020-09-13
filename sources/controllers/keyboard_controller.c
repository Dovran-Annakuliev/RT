#include "../../includes/rtv1.h"

static	int	update_samples(t_rt *data)
{
	data->samples = data->samples % 16 == 0 ? 1 : data->samples * 2;
	free(data->randoms);
	data->randoms = new_random_array(data->width, data->height, data->samples);
	printf("samples = %d\n", data->samples);
	return (1);
}

//DELETE
static	int	update_light(t_rt *data, SDL_Event *e)
{
	if (e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_DOWN
		|| e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_RIGHT)
	{
		e->key.keysym.sym == SDLK_UP ? data->lights[1].pos.z-- : 0;
		e->key.keysym.sym == SDLK_DOWN ? data->lights[1].pos.z++ : 0;
		e->key.keysym.sym == SDLK_LEFT ? data->lights[1].pos.x-- : 0;
		e->key.keysym.sym == SDLK_RIGHT ? data->lights[1].pos.x++ : 0;
		return (1);
	}
	return (0);
}

void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
		data->update_status = e->key.keysym.sym == SDLK_p ? update_samples(data) : update_light(data, e);
}
