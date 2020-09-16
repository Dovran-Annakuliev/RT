#include "../includes/rtv1.h"

void		set_cameras(t_camera *cameras,
				int camera_size, int width, int height)
{
	int i;

	i = 0;
	while (i < camera_size)
	{
		init_camera(&cameras[i], width, height);
		update_camera(&cameras[i]);
		i++;
	}
}

void		init_camera(t_camera *camera, int width, int height)
{
	camera->image_aspect_ratio = (float)width / (float)height;
	camera->vertical_fov = camera->vertical_fov;
	camera->h_angle = (float)tan(camera->vertical_fov / 2 * M_PI / 180);
	camera->viewport_height = camera->viewport_height * camera->h_angle;
	camera->viewport_width = camera->viewport_height
								* camera->image_aspect_ratio;
	camera->look_from = camera->look_from;
	camera->look_at = camera->look_at;
	camera->vec_up = (cl_float3){0.0f, 1.0f, 0.0f};
	camera->origin = (cl_float3){0.0f, 0.0f, 0.0f};
	camera->horizontal = (cl_float3){0.0f, 0.0f, 0.0f};
	camera->vertical = (cl_float3){0.0f, 0.0f, 0.0f};
	camera->upper_left_corner = (cl_float3){0.0f, 0.0f, 0.0f};
}

void		update_camera(t_camera *camera)
{
	cl_float3 w;
	cl_float3 u;
	cl_float3 v;

	w = vec_sub(camera->look_from, camera->look_at);
	w = vec_normalize(w);
	u = vec_cross(camera->vec_up, w);
	u = vec_normalize(u);
	v = vec_cross(w, u);
	camera->origin = camera->look_from;
	camera->horizontal = mult_vec_scal(u, camera->viewport_width);
	camera->vertical = mult_vec_scal(v, camera->viewport_height);
	camera->upper_left_corner = vec_sub(camera->origin,
									mult_vec_scal(camera->horizontal, 0.5));
	camera->upper_left_corner = vec_add(camera->upper_left_corner,
									mult_vec_scal(camera->vertical, 0.5));
	camera->upper_left_corner = vec_sub(camera->upper_left_corner, w);
}
