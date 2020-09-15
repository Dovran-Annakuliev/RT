#include "../../includes/rtv1.h"

static	int	update_samples(t_rt *data)
{
	data->samples = data->samples % 16 == 0 ? 1 : data->samples * 2;
	free(data->randoms);
	data->randoms = new_random_array(data->width, data->height, data->samples);
	printf("samples = %d\n", data->samples);
	return (1);
}

void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
		data->update_status = e->key.keysym.sym == SDLK_p ? update_samples(data) : 0;
}
