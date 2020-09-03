#include "../includes/rtv1.h"

static	char		*return_path()
{
	return ("kernels/raytrace.cl");
}

t_rt				*init_data()
{
	t_rt *data;

	data = (t_rt*)malloc(sizeof(t_rt));
	!data ? error(MALLOC_ERROR, "Malloc error") : 0;
	SDL_Init(SDL_INIT_EVERYTHING) < 0 ? error(SDL_INIT_ERROR, SDL_GetError()) : 0;
	IMG_Init(IMG_INIT_PNG) < 0 ? error(IMG_INIT_ERROR, IMG_GetError()) : 0;
	data->window = SDL_CreateWindow("RTv1", 0, 0, 0, 0,  SDL_WINDOW_FULLSCREEN_DESKTOP);
	!(data->window) ? error(WINDOW_CREATE_ERROR, SDL_GetError()) : 0;
	SDL_GetWindowSize(data->window, &data->width, &data->height);
	ft_printf("width = %d, height = %d\n", data->width, data->height);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	!(data->renderer) ? error(RENDER_INIT_ERROR, SDL_GetError()) : 0;
	ft_printf("render_good\n");
	data->texture = SDL_CreateTexture(data->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, data->width, data->height);
	!(data->texture) ? error(TEXTURE_LOAD_ERROR, SDL_GetError()) : 0;
	ft_printf("texture_good\n");
	data->cl_path = return_path();
	ft_printf("path_good\n");
	data->o[0] = new_sphere((cl_float3){10.0f, 0.0f, -15.0f}, 2.0f, new_material((cl_float4){255, 0, 0, 0}));
	data->o[1] = new_sphere((cl_float3){0.0f, 0.0f, -10.0f}, 1.0f, new_material((cl_float4){0, 255, 0, 0}));
	data->o[2] = new_sphere((cl_float3){-20.0f, 0.0f, -15.0f}, 4.0f, new_material((cl_float4){0, 0, 255, 0}));
	ft_printf("objects_good\n");
	return (data);
}

void 	close_rt(t_rt *data)
{
	SDL_DestroyTexture(data->texture);
	IMG_Quit();
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	free(data);
	data = NULL;
}
