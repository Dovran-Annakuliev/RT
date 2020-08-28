#ifndef RTV1_H
#define RTV1_H

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>
#else
# include <GL/opengl.h>
#endif

#include "../libft/includes/libft.h"
#include "../SDL2.framework/Headers/SDL.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"
#include "error_codes.h"
#include "vectors.h"
#include "rgba.h"
#include "sphere.h"

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

typedef struct			s_rt
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	Uint32				*pixels;
	int 				pitch;
	int 				width;
	int 				height;
	t_cl				*cl;
	char 				*cl_path;
}						t_rt;

/*
 ** ---init_functions---
 */

t_rt					*init_data();
void					close_rt(t_rt *data);

/*
** ---OpenCl functions---
*/

void					cl_init(t_cl *cl, int width, int height);
void					cl_free(t_cl *cl);
char					**get_kernel_source(t_cl *cl, char *path);

/*
 ** ---rendering---
 */

int					*render(t_cl *cl, int w, int h);

/*
 ** ---coloring---
 */

void					update_texture(SDL_Texture *texture, int width, int height, int *r);

/*
 ** ---controls---
 */

void					controller(SDL_Event *e);
void					keyboard_controller(SDL_Event *e);
void					mouse_controller(SDL_Event *e);

/*
 ** ---error---
 */

void					error(int err, const char *message);

#endif
