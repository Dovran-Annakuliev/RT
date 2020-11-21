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

static void print_obj(t_rt *data){
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

void print_light(t_rt *data){
	for (int i = 0; i < data->parse.light_size; i++){
		if (data->parse.light[i].type == 0)
			printf("light[%d]: ambient:\n\tintensity = %f\n", i, data->parse.light[i].intensity);
		else if (data->parse.light[i].type == 1)
			printf("light[%d]: directional:\n\tdirection = %f, %f, %f\n\tintensity = %f",
		  		i,
		  		data->parse.light[i].dir.x, data->parse.light[i].dir.y, data->parse.light[i].dir.z,
		  		data->parse.light[i].intensity);
		else if (data->parse.light[i].type == 2)
			printf("light[%d]: point:\n\tdirection = %f, %f, %f\n\tintensity = %f\n\tcolor = %f, %f, %f, %f\n",
		  		i,
				data->parse.light[i].dir.x, data->parse.light[i].dir.y, data->parse.light[i].dir.z,
				data->parse.light[i].intensity,
				data->parse.light[i].clr.x, data->parse.light[i].clr.y, data->parse.light[i].clr.z, data->parse.light[i].clr.w);
		else if (data->parse.light[i].type == 3)
			printf("light[%d]: sphere:\n\tdirection = %f, %f, %f\n\tintensity = %f\n\tradius = %f\n\tcolor = %f, %f, %f, %f\n",
				   i,
				   data->parse.light[i].dir.x, data->parse.light[i].dir.y, data->parse.light[i].dir.z,
				   data->parse.light[i].intensity,
				   data->parse.light[i].r,
				   data->parse.light[i].clr.x, data->parse.light[i].clr.y, data->parse.light[i].clr.z, data->parse.light[i].clr.w);
		else if (data->parse.light[i].type == 4)
			printf("light[%d]: rectangle:\n\tdirection = %f, %f, %f\n\tintensity = %f\n\twidth = %f\n\theight = %f\n\tnormal = %f, %f, %f\n\tcolor = %f, %f, %f, %f\n",
				   i,
				   data->parse.light[i].dir.x, data->parse.light[i].dir.y, data->parse.light[i].dir.z,
				   data->parse.light[i].intensity,
				   data->parse.light[i].width,
				   data->parse.light[i].height,
				   data->parse.light[i].normal.x, data->parse.light[i].normal.y, data->parse.light[i].normal.z,
				   data->parse.light[i].clr.x, data->parse.light[i].clr.y, data->parse.light[i].clr.z, data->parse.light[i].clr.w);
	}
}

void print_camera(t_rt *data){
	for (int i = 0; i < data->parse.camera_size; i++){
		printf("camera[%d]:\n\tlook_from = %f, %f, %f\n\tlook_at = %f, %f, %f\n\tvertical_fov = %f\n\tviewport_height = %f\n",
			i,
			data->parse.camera[i].look_from.x, data->parse.camera[i].look_from.y, data->parse.camera[i].look_from.z,
		   	data->parse.camera[i].look_at.x, data->parse.camera[i].look_at.y, data->parse.camera[i].look_at.z,
		  	data->parse.camera[i].vertical_fov,
		 	data->parse.camera[i].viewport_height);
	}
}

int				main(int ac, char **av)
{
	t_rt		*data;

	ac != 2 ? error(INVALID_ARGUMENTS, "INVALID_ARGUMENTS") : 0;
	data = init_data();
	read_arg(av[1], data);

	print_obj(data);
	print_light(data);
	print_camera(data);

	set_cameras(data->parse.camera, data->parse.camera_size, data->w, data->h);
	calculate_triangle_normals(&data->parse);
	data->cl.kernel_source = get_kernel_source(&data->cl, data->cl_path);
	cl_init(&data->cl, data->w, data->h);
	main_loop(data);
	close_rt(data);
	printf("Exit program\n");
	return (0);
}
