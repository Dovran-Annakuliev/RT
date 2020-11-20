#ifndef RTV1_H
# define RTV1_H

# ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenCL/opencl.h>
#  include "../SDL2.framework/Headers/SDL.h"
# else
#  include <GL/gl.h>
#  include <CL/cl.h>
#  include <SDL2/SDL.h>
# endif

# include <time.h>
# include "../libft/includes/libft.h"
# include "../SDL2_image.framework/Headers/SDL_image.h"
# include "error_codes.h"
# include "vectors.h"
# include "objects.h"
# include "lights.h"
# include "camera.h"
# include "parser.h"

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
	int					update_status;
	int					pitch;
	int					w;
	int					h;
	t_cl				cl;
	char				*cl_path;
	int					samples;
	int					current_camera;
	float				*randoms;
	float				*res;
	t_parse				parse;

}						t_rt;

typedef struct		s_buffers
{
	cl_mem			output_buffer;
	cl_mem			obj_buffer;
	cl_mem			light_buffer;
	cl_mem			rand_buffer;
}					t_buffers;

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
void					parse_sphere(int fd, t_rt *data);
void					parse_plane(int fd, t_rt *data);
void					parse_cone(int fd, t_rt *data);
void					parse_cylinder(int fd, t_rt *data);
void					parse_triangle(int fd, t_rt *data);
void					parse_rectangle(int fd, t_rt *data);
void					parse_circle(int fd, t_rt *data);
void					parse_object3d(int fd, t_rt *data);
void					parse_object3d_file(t_rt *data, char *sourse);
void					parce_ambient_light(int fd, t_rt *data);
void					parce_point_light(int fd, t_rt *data);
void					parce_directional_light(int fd, t_rt *data);
void					parse_camera(int fd, t_rt *data);

/*
** ---parse_utilities---
*/

float					parse_float(char *line, char *type);
cl_float				parse_cl_float(char *line, char *type);
cl_float3				parse_cl_float3(char *line, char *type);
cl_float4				parse_cl_float4(char *line, char *type);
cl_float3 				parse_object3d_vertex(char *line);
cl_float3				parse_object3d_normal(char *line);
cl_float3				parse_object3d_face(char *line, t_rt *data);
void					read_object3d(int fd, t_rt *data);
int						parse_type_light(char *line);
void					parse_light_sphere(int fd, t_rt *data);
void					parse_light_point(int fd, t_rt *data);
void					parse_light_rect(int fd, t_rt *data);
void					parse_material(int fd, t_obj *obj);
void					free_split(char ***split);
char					**ft_strsplit_space(const char *s);
int						ft_count_words_split(const char **s);
float					ft_atof(const char *str);
void					clamp_color(cl_float4 *color);
cl_int					is_counter_clockwise(t_obj triangle, cl_float3 camera_dir);
void					get_triangle_orientations(t_parse *p, cl_float3 camera_dir);
void					calculate_triangle_normals(t_parse *p);


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

void					update_texture(SDL_Texture *texture,
									int width, int height, float *r);

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
