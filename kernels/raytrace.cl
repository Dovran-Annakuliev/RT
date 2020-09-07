typedef struct	s_material
{
	float4		diff_color;
}				t_material;

typedef struct			s_camera
{
	float				viewport_width;
	float				viewport_height;
	float				image_aspect_ratio;
	float				vertical_fov;
	float				h_angle;
	float3				look_from;
	float3				look_at;
	float3				vec_up;
	float3				origin;
	float3				horizontal;
	float3				vertical;
	float3				lower_left_corner;
}						t_camera;

typedef struct			s_obj
{
	int 				type;
	float3			s_center;
	float			s_radius;
	float3			p_pos;
	float3			p_normal;
	t_material			material;
}				t_obj;

typedef struct		s_light
{
	float3			pos;
	float			intensity;
}					t_light;

static	float		solve_eq(float a, float b, float c, float t_min, float t_max)
{
	float dis = b * b - 4 * a * c;
	if (dis < 0.0f)
		return (0.0f);
	dis = sqrt(dis);
	float x1 = (-b - dis) * (1 / (2 * a));
	if (x1 > t_min && x1 < t_max)
		return (x1);
	float x2 = (-b + dis) * (1 / (2 * a));
	if (x2 > t_min && x2 < t_max)
		return (x2);
	return (0.0f);
}

static		bool		sphere_intersect(float3 orig, float3 dir, __global t_obj* objects, float3 *hit_pos, float3 *N, float4 *color)
{
	float	closest_dist = FLT_MAX;

	for(int i = 0; i < 4; i++)
	{
		float	dist_i;

		float3 center = (float3)(objects[i].s_center.x, objects[i].s_center.y, objects[i].s_center.z);
		float radius = (float)(objects[i].s_radius);

		float3 L = orig - center;
		float a = dot(dir, dir);
		float b = 2 * dot(L, dir);
		float c = dot(L, L) - radius * radius;
		dist_i = solve_eq(a, b, c, 0.001f, closest_dist);

		if (dist_i != 0.0f && dist_i < closest_dist)
		{
			closest_dist = dist_i;
			*hit_pos = orig + dir * dist_i;
			*N = normalize(*hit_pos - center);
			*color = objects[i].material.diff_color;
		}
	}
	return (closest_dist < 100);
}

static	float4  get_light(float3 hit_pos, float3 N, t_light light, float4 color)
{
	float	df_light_int = 0.0f;
	float3	light_dir =  (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_pos;
	float dot_light_dir = dot(N, light_dir);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(light_dir));
	return(color * df_light_int);

}

static	float4	trace(float3 orig, float3 dir, __global t_obj *objects, t_light light)
{
	float3	hit_pos, N;
	float4	color;

	if (!sphere_intersect(orig, dir, objects, &hit_pos, &N, &color))
		return((float4)(100.0f, 100.0f, 100.0f, 0.0f));

	color = get_light(hit_pos, N, light, color);

	return (color);
}

__kernel void raytrace(t_camera camera, __global t_obj* objects, __global float* randoms, int samples, t_light light, __global float4* output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	float Px, Py;
	float3 dir;
	if (x == width/ 2 && y == height / 2)
			printf("\n");


	/*
	float3 w = normalize(camera.look_from - camera.look_at);
	float3 u = normalize(cross(camera.vec_up, w));
	float3 v = cross(w, u);

	camera.origin = camera.look_from;
	camera.horizontal = camera.viewport_width * u;
	camera.vertical = camera.viewport_height * v;
	camera.lower_left_corner = camera.origin - camera.horizontal/2 - camera.vertical/2 - w;
	*/

	/*
	Px = ((float)x) / (width - 1);
    Py = ((float)y) / (height - 1);
    dir = camera.lower_left_corner + Px * camera.horizontal + Py * camera.vertical - camera.origin;
    dir = normalize(dir);
    output[y * width + x] = trace(camera.origin, dir, objects, light);
    */

	output[y * width + x] = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i < samples; i++)
	{
		Px = ((float)x + randoms[(y * width + x) * samples + i]) / (width - 1);
		Py = ((float)y + randoms[(y * width + x) * samples + i]) / (height - 1);
		dir = camera.lower_left_corner + Px * camera.horizontal + Py * camera.vertical - camera.origin;
		dir = normalize(dir);
		output[y * width + x] += trace(camera.origin, dir, objects, light);
	}

	output[y * width + x] /= samples;
}
