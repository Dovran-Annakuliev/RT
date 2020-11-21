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

static void check_obj(t_rt *data){
	printf("obj_size = %d\n", data->parse.obj_size);
	for (int i = 0; i < data->parse.obj_size; i++){
		if (data->parse.obj[i].type == 0){
			printf("obj[%d]: sphere:\n\ts_center = %f, %f, %f\n\ts_radius = %f\n",
		  		i,
		  		data->parse.obj[i].s_center.x, data->parse.obj[i].s_center.y, data->parse.obj[i].s_center.z,
		  		data->parse.obj[i].s_radius);
		}
		else if (data->parse.obj[i].type == 1){
			printf("obj[%d]: plane:\n\tp_pos = %f, %f, %f\n\tp_normal = %f, %f, %f\n",
				   i,
				   data->parse.obj[i].p_pos.x, data->parse.obj[i].p_pos.y, data->parse.obj[i].p_pos.z,
				   data->parse.obj[i].p_normal.x, data->parse.obj[i].p_normal.y, data->parse.obj[i].p_normal.z);
		}
		else if (data->parse.obj[i].type == 2){
			printf("obj[%d]: cone:\n\tcone_pos = %f, %f, %f\n\tcone_angle = %f, %f, %f\n\tcone_axis = %f, %f, %f\n",
				   i,
				   data->parse.obj[i].cone_pos.x, data->parse.obj[i].cone_pos.y, data->parse.obj[i].cone_pos.z,
				   data->parse.obj[i].cone_angle,
				   data->parse.obj[i].cone_axis.x, data->parse.obj[i].cone_axis.y, data->parse.obj[i].cone_axis.z);
		}
		else if (data->parse.obj[i].type == 3){
			printf("obj[%d]: cylinder:\n\tcyl_pos = %f, %f, %f\n\tcyl_r = %f, %f, %f\n\tcyl_axis = %f, %f, %f\n",
				   i,
				   data->parse.obj[i].cyl_pos.x, data->parse.obj[i].cyl_pos.y, data->parse.obj[i].cyl_pos.z,
				   data->parse.obj[i].cyl_r,
				   data->parse.obj[i].cyl_axis.x, data->parse.obj[i].cyl_axis.y, data->parse.obj[i].cyl_axis.z);
		}
		else if (data->parse.obj[i].type == 4){
			printf("obj[%d]: triangle:\n\ttr_0 = %f, %f, %f\n\ttr_1 = %f, %f, %f\n\ttr_2 = %f, %f, %f\n\ttr_normal = %f, %f, %f\n",
				   i,
				   data->parse.obj[i].tr_0.x, data->parse.obj[i].tr_0.y, data->parse.obj[i].tr_0.z,
				   data->parse.obj[i].tr_1.x, data->parse.obj[i].tr_1.y, data->parse.obj[i].tr_1.z,
				   data->parse.obj[i].tr_2.x, data->parse.obj[i].tr_2.y, data->parse.obj[i].tr_2.z,
				   data->parse.obj[i].tr_normal.x, data->parse.obj[i].tr_normal.y, data->parse.obj[i].tr_normal.z);
		}
		else if (data->parse.obj[i].type == 5){
			printf("obj[%d]: rectangle:\n\trec_0 = %f, %f, %f\n\trec_1 = %f, %f, %f\n\trec_2 = %f, %f, %f\n\trec_3 = %f, %f, %f\n",
				   i,
				   data->parse.obj[i].rec_0.x, data->parse.obj[i].rec_0.y, data->parse.obj[i].rec_0.z,
				   data->parse.obj[i].rec_1.x, data->parse.obj[i].rec_1.y, data->parse.obj[i].rec_1.z,
				   data->parse.obj[i].rec_2.x, data->parse.obj[i].rec_2.y, data->parse.obj[i].rec_2.z,
				   data->parse.obj[i].rec_3.x, data->parse.obj[i].rec_3.y, data->parse.obj[i].rec_3.z);
		}
		else if (data->parse.obj[i].type == 6){
			printf("obj[%d]: circle:\n\tcrcl_pos = %f, %f, %f\n\tcrcl_normal = %f, %f, %f\n\tcrcl_r = %f\n",
				   i,
				   data->parse.obj[i].crcl_pos.x, data->parse.obj[i].crcl_pos.y, data->parse.obj[i].crcl_pos.z,
				   data->parse.obj[i].crcl_normal.x, data->parse.obj[i].crcl_normal.y, data->parse.obj[i].crcl_normal.z,
				   data->parse.obj[i].crcl_r);
		}
		else
			printf("unknown_type[%d] = %d\n", i, data->parse.obj[i].type);
	}
}

int				main(int ac, char **av)
{
	t_rt		*data;

	ac != 2 ? error(INVALID_ARGUMENTS, "INVALID_ARGUMENTS") : 0;
	data = init_data();
	read_arg(av[1], data);

	check_obj(data);

	set_cameras(data->parse.camera, data->parse.camera_size, data->w, data->h);
	calculate_triangle_normals(&data->parse);
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_path);
	cl_init(&data->cl, data->w, data->h);
	main_loop(data);
	close_rt(data);
	printf("Exit program\n");
	return (0);
}
