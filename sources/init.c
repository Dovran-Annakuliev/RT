#include "../includes/rtv1.h"

static	char		*return_path()
{
	return ("/Users/ltammie/RTv1/kernels/raytrace.cl");
}

float	*new_random_array(int w, int h, int samples)
{
	float		*res;
	int			i;

	srand((unsigned int)time(NULL));
	if (!(res = (float*)malloc(sizeof(float) * w * h * samples)))
		error(MALLOC_ERROR, "renderer malloc error");
	i = 0;

	while (i < h * w * samples)
	{
		res[i] = samples == 1 ? 0 : ((float)rand() / (float)RAND_MAX);
		i++;
	}
	return (res);
}


t_rt				*init_data()
{
	t_rt *data;

	data = (t_rt*)malloc(sizeof(t_rt));
	!data ? error(MALLOC_ERROR, "Malloc error") : 0;
	SDL_Init(SDL_INIT_EVERYTHING) < 0 ? error(SDL_INIT_ERROR, SDL_GetError()) : 0;
	IMG_Init(IMG_INIT_PNG) < 0 ? error(IMG_INIT_ERROR, IMG_GetError()) : 0;
//	data->window = SDL_CreateWindow("RTv1",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
	data->window = SDL_CreateWindow("RTv1", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	!(data->window) ? error(WINDOW_CREATE_ERROR, SDL_GetError()) : 0;
	SDL_GetWindowSize(data->window, &data->width, &data->height);
	ft_printf("width = %d, height = %d\n", data->width, data->height);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	!(data->renderer) ? error(RENDER_INIT_ERROR, SDL_GetError()) : 0;
	data->texture = SDL_CreateTexture(data->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, data->width, data->height);
	!(data->texture) ? error(TEXTURE_LOAD_ERROR, SDL_GetError()) : 0;
	data->cl_path = return_path();
	init_camera(&data->camera, data->width, data->height);
	update_camera(&data->camera);
	data->o[0] = new_cone((cl_float3){0.0f, 0.0f, -10.0f}, 30.0f, (cl_float3){0.0f, 1.0f, 0.0f}, new_material((cl_float4){255, 255, 255, 0}, 500, 0.3f));
	data->o[1] = new_cone((cl_float3){0.0f, 0.0f, -10.0f}, 30.0f, (cl_float3){1.0f, 0.0f, 0.0f}, new_material((cl_float4){255, 255, 255, 0}, 500, 0.3f));
	data->o[2] = new_sphere((cl_float3){0.0f, 0.0f, 0.0f}, 0.5f, new_material((cl_float4){255, 0, 0, 0}, 50, 0.3f));
	data->o[3] = new_plane((cl_float3){0.0f, -1.0f, 0.0f}, (cl_float3){0.0f, 1.0f, 0.0f}, new_material((cl_float4){0, 255, 255, 0}, 50, 0.3f));
	data->lights[0] = new_ambient_light(0.3f);
	data->lights[1] = new_point_light((cl_float3){0.0f, 10.0f, 10.0f}, 0.3f);
	data->lights[2] = new_directional_light((cl_float3){2.0f, 1.0f, 10.0f}, 0.5f);
	data->samples = 1;
	data->randoms = new_random_array(data->width, data->height, data->samples);
	if (!(data->res = (float*)malloc(sizeof(float) * data->width * data->height * 4)))
		error(MALLOC_ERROR, "result buffer malloc error");
	data->update_status = 1;
	return (data);
}

void 	close_rt(t_rt *data)
{
	SDL_DestroyTexture(data->texture);
	IMG_Quit();
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	SDL_Quit();
	free(data->randoms);
	free(data->res);
	free(data->parse.obj);
	free(data->parse.light);
	free(data->parse.camera);
	free(data);
	data = NULL;
}
