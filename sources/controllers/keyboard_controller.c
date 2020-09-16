#include "../../includes/rtv1.h"

static	int	update_samples(t_rt *data)
{
	data->samples = data->samples % 16 == 0 ? 1 : data->samples * 2;
	free(data->randoms);
	data->randoms = new_random_array(data->w, data->h, data->samples);
	printf("samples = %d\n", data->samples);
	return (1);
}

static	int		switch_camera(t_rt *data, int key)
{
	key == SDLK_LEFT ? data->current_camera-- : data->current_camera++;
	data->current_camera = data->current_camera < 0 ? 0 :
			data->current_camera % data->parse.camera_size;
	return (1);
}

void 		keyboard_controller(SDL_Event *e, t_rt *data)
{
	if (e->type == SDL_KEYDOWN)
	{
		data->update_status = e->key.keysym.sym == SDLK_p ? update_samples(data) : data->update_status;
		data->update_status = (e->key.keysym.sym == SDLK_LEFT || e->key.keysym.sym == SDLK_RIGHT) ?
				switch_camera(data, e->key.keysym.sym) : data->update_status;
	}
}
