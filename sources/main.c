#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;
	SDL_Event e;
	int quit;

	data = init_data();
	quit = 0;
	while (quit != 1)
	{
		SDL_RenderClear(data->renderer);
		update_texture(data);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			else
				controller(&e);
		}
	}
	close_rt(data);
	return (0);
}
