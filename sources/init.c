#include "../includes/rtv1.h"

t_rt	*init_data()
{
	t_rt *data;

	data = (t_rt*)malloc(sizeof(t_rt));
	!data ? error(MALLOC_ERROR) : 0;
	!SDL_GetCurrentDisplayMode(0, data->mode) ? error(DMODE_ERROR) : 0;
	data->width = data->mode->w;
	data->height = data->mode->h;
	SDL_Init(SDL_INIT_EVERYTHING) < 0 ? error(SDL_INIT_ERROR) : 0;
	IMG_Init(IMG_INIT_JPG) < 0 ? error(IMG_INIT_ERROR) : 0;
	data->window = SDL_CreateWindow("RTv1", WINPOS_X, WINPOS_Y, data->width, data->height, SDL_WINDOW_FULLSCREEN);
	!(data->window) ? error(WINDOW_CREATE_ERROR) : 0;
	data->surface = SDL_GetWindowSurface(data->window);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	data->texture = IMG_LoadTexture(data->renderer, "../textures/1.jpeg");
	return (data);
}

void 	close_rt(t_rt *data)
{
	SDL_DestroyTexture(data->texture);
	IMG_Quit();
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	free(data);
	data = NULL;
}
