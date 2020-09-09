#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;
	SDL_Event e;
	int quit;

	data = init_data();
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_path);
	cl_init(&data->cl, data->width, data->height);
	quit = 0;
	while (quit != 1)
	{
		SDL_RenderClear(data->renderer);
		render(data);
		update_texture(data->texture, data->width, data->height, data->res);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			else
				controller(&e, data);
		}
	}
	close_rt(data);

	return (0);
}
