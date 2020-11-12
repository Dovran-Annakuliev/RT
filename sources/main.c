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
	ft_printf("pos: %f, %f, %f\n", data->parse.obj[0].cyl_pos.x,
			  data->parse.obj[0].cyl_pos.y,
			  data->parse.obj[0].cyl_pos.z);

	ft_printf("tri_0: %f, %f, %f\n", data->parse.obj[1].tr_0.x,
			  data->parse.obj[1].tr_0.y,
			  data->parse.obj[1].tr_0.z);

	ft_printf("tri_1: %f, %f, %f\n", data->parse.obj[1].tr_1.x,
			  data->parse.obj[1].tr_1.y,
			  data->parse.obj[1].tr_1.z);

	ft_printf("tri_2: %f, %f, %f\n", data->parse.obj[1].tr_2.x,
			  data->parse.obj[1].tr_2.y,
			  data->parse.obj[1].tr_2.z);

	ft_printf("col: %f, %f, %f\n", data->parse.obj[1].material.diff_color.x,
			  data->parse.obj[1].material.diff_color.y,
			  data->parse.obj[1].material.diff_color.z);

	ft_printf("spec: %f\n", data->parse.obj[1].material.specular);

	ft_printf("ref: %f\n", data->parse.obj[1].material.reflection);

	set_cameras(data->parse.camera, data->parse.camera_size, data->w, data->h);
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_path);
	cl_init(&data->cl, data->w, data->h);
	main_loop(data);
	close_rt(data);
	return (0);
}


//ft_printf("pos: %f, %f, %f\n", data->parse.obj[0].cyl_pos.x,
//data->parse.obj[0].cyl_pos.y,
//data->parse.obj[0].cyl_pos.z);
//
//ft_printf("tri_0: %f, %f, %f\n", data->parse.obj[1].tr_0.x,
//data->parse.obj[1].tr_0.y,
//data->parse.obj[1].tr_0.z);
//
//ft_printf("tri_1: %f, %f, %f\n", data->parse.obj[1].tr_1.x,
//data->parse.obj[1].tr_1.y,
//data->parse.obj[1].tr_1.z);
//
//ft_printf("tri_2: %f, %f, %f\n", data->parse.obj[1].tr_2.x,
//data->parse.obj[1].tr_2.y,
//data->parse.obj[1].tr_2.z);
//
//ft_printf("col: %f, %f, %f\n", data->parse.obj[1].material.diff_color.x,
//data->parse.obj[1].material.diff_color.y,
//data->parse.obj[1].material.diff_color.z);
//
//ft_printf("spec: %f\n", data->parse.obj[1].material.specular);
//
//ft_printf("ref: %f\n", data->parse.obj[1].material.reflection);
