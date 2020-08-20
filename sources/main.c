#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;
	SDL_Event event;

	data = init_data();
	while (1)
	{
		SDL_RenderClear(data->renderer);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	close_rt(data);
	return (0);
}
