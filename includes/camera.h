#ifndef CAMERA_H
#define CAMERA_H

typedef struct			s_camera
{
	float				viewport_width;
	float				viewport_height;
	float				image_aspect_ratio;
	float				vertical_fov;
	float				h_angle;
	cl_float3			look_from;
	cl_float3			look_at;
	cl_float3			vec_up;
	cl_float3			origin;
	cl_float3			horizontal;
	cl_float3			vertical;
	cl_float3			upper_left_corner;

}						t_camera;

/*
** ---camera_functions---
*/

void					init_camera(t_camera *viewport, int width, int height);
void					update_camera(t_camera *camera);
void					set_cameras(t_camera *cameras, int camera_size, int width, int height);
void					print_camera_info(t_camera camera, int id);


#endif
