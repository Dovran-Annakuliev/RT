#include "../includes/rtv1.h"

t_rt	*init_data()
{
	t_rt *data;

	data = (t_rt*)malloc(sizeof(t_rt));
	!data ? error(MALLOC_ERROR) : 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		error(INIT_ERROR);
	data->window = SDL_CreateWindow("RTv1", WINPOS_X, WINPOS_Y, 800, 600, SDL_WINDOW_FULLSCREEN);
	!(data->window) ? error(WINDOW_CREATE_ERROR) : 0;
	SDL_GetWindowSize(data->window, &data->width, &data->height);
	data->surface = SDL_GetWindowSurface(data->window);
	data->surface = IMG_;
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	data->texture = load;
	return (data);
}

void 	close_rt(t_rt *data)
{
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	free(data);
	data = NULL;
}
