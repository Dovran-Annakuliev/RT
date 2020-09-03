#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;
	SDL_Event e;
	int quit;
	float *res;

	data = init_data();
	ft_printf("init\n");
	data->cl->kernel_source = get_kernel_source(data->cl, data->cl_path);
	ft_printf("kernel_source\n");

//	cl_init(data->cl, data->width, data->height);
//	quit = 0;
//	while (quit != 1)
//	{
//		SDL_RenderClear(data->renderer);
//		res = render(data->cl, data->width, data->height, data->o);
//		update_texture(data->texture, data->width, data->height, res);
//		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
//		SDL_RenderPresent(data->renderer);
//		while (SDL_PollEvent(&e))
//		{
//			if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
//				quit = 1;
//			else
//				controller(&e, data);
//		}
//	}
	close_rt(data);
	return (0);
}
