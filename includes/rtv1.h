#ifndef RTV1_H
#define RTV1_H

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>
#else
# include <GL/opengl.h>
# include <CL/opencl.h>
#endif

#include "../libft/includes/libft.h"
#include "../SDL2.framework/Headers/SDL.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"
#include <time.h>
#include "error_codes.h"
#include "vectors.h"
#include "rgba.h"
#include "lights.h"
#include "objects.h"
#include "parser.h"

typedef struct			s_cl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	char				**kernel_source;
	int					count;
	size_t				dim;
	size_t				global_size[2];
}						t_cl;

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

typedef struct			s_rt
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	Uint32				*pixels;
	int					update_status;
	int					pitch;
	int					width;
	int					height;
	t_cl				cl;
	t_camera			camera;
	char 				*cl_path;
	t_obj				o[4];
	t_light				lights[3];
	int					samples;
	float				*randoms;
	float				*res;

	t_parse				parse;

}						t_rt;

/*
** ---init_functions---
*/

t_rt					*init_data();
void					close_rt(t_rt *data);
float					*new_random_array(int w, int h, int samples);

/*
** ---parse_functions---
*/

void					read_arg(char *source, t_rt *data);
float					ft_atof(const char *str);
void					parse_sphere(int fd, t_rt *data);
void					parse_plane(int fd, t_rt *data);
void parce_ambient_light(int fd, t_rt *data);
void parce_point_light(int fd, t_rt *data);
void parce_directional_light(int fd, t_rt *data);

/*
** ---parse_utilities---
*/

float					parse_float(char *line);
cl_float				parse_cl_float(char *line);
cl_float3				parse_cl_float3(char *line);
cl_float4				parse_cl_float4(char *line);
void					parse_material(int fd, t_obj *obj);
void					free_split(char ***split);

/*
** ---camera_functions---
*/
void					init_camera(t_camera *viewport, int width, int height);
void					update_camera(t_camera *camera);


/*
** ---OpenCl_functions---
*/

void					cl_init(t_cl *cl, int width, int height);
void					cl_free(t_cl *cl);
char					**get_kernel_source(t_cl *cl, char *path);

/*
** ---rendering---
*/

void					render(t_rt *rt);

/*
** ---coloring---
*/

void					update_texture(SDL_Texture *texture, int width, int height, float *r);

/*
** ---controls---
*/

void					controller(SDL_Event *e, t_rt *data);
void					keyboard_controller(SDL_Event *e, t_rt *data);
void					mouse_controller(SDL_Event *e, t_rt *data);

/*
** ---error---
*/

void					error(int err, const char *message);

#endif
