#include "../includes/rtv1.h"

static	void	main_loop(t_rt *data)
{
	int			quit;
	SDL_Event	e;

	quit = 0;
	while (quit != 1)
	{
		SDL_RenderClear(data->renderer);
		data->update_status == 1 ? render(data) : 0;
		update_texture(data->texture, data->w, data->h, data->res);
		SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
		SDL_RenderPresent(data->renderer);
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT ||
			(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
			else
				controller(&e, data);
		}
	}
}

int				main(int ac, char **av)
{
	t_rt		*data;

	ac != 2 ? error(INVALID_ARGUMENTS, "INVALID_ARGUMENTS") : 0;
	data = init_data();
	read_arg(av[1], data);
	set_cameras(data->parse.camera, data->parse.camera_size, data->w, data->h);
	calculate_triangle_normals(&data->parse);
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_path);
	cl_init(&data->cl, data->w, data->h);
	main_loop(data);
	close_rt(data);
	return (0);
}
