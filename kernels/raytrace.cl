typedef struct	s_material
{
	float4		diff_color;
	float		specular;
	float		reflection;
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
	float3				upper_left_corner;
}						t_camera;

typedef struct			s_obj
{
	int 				type;
	float3				s_center;
	float				s_radius;
	float3				p_pos;
	float3				p_normal;
	float3				cone_pos;
   	float				cone_angle;
    float3				cone_axis;
	t_material			material;
}						t_obj;

typedef struct		s_light
{
	int				type;
	float3			pos;
	float3			dir;
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

static	float	intersect_sphere(t_obj	*sphere, float3 orig, float3 dir)
{
	float dist;

	float3 center = (float3)(sphere->s_center.x, sphere->s_center.y, sphere->s_center.z);
	float radius = (float)(sphere->s_radius);

	float3 L = orig - center;
	float a = dot(dir, dir);
	float b = 2 * dot(L, dir);
	float c = dot(L, L) - radius * radius;

	dist = solve_eq(a, b, c, 0.001f, FLT_MAX);
	return (dist);
}

static	float	intersect_plane(t_obj	*plane, float3 orig, float3 dir)
{
	float dist;

	float a = dot(plane->p_normal, dir);
	if (fabs(a) < 0.001f)
		return (0);
	float b = -(dot(orig - plane->p_pos, plane->p_normal)) / a;
	dist = b < 0.001f ? 0 : b;
	return (dist);
}

static	float	intersect_cone(t_obj	*cone, float3 orig, float3 dir)
{
	float dist;

	float3	X = orig - cone->cone_pos;
	float	d_v = dot(dir, cone->cone_axis);
	float	x_v = dot(X, cone->cone_axis);
	float	k = tan(cone->cone_angle * M_PI_F / 180);
	float	temp = 1 + k * k;

	float a = dot(dir, dir) - temp * d_v * d_v;
	float b = 2.0 * (dot(dir, X) - temp * d_v * x_v);
	float c = dot(X,X) - temp * x_v * x_v;

	dist = solve_eq(a, b, c, 0.001f, FLT_MAX);
	return (dist);
}

static	float3	get_sphere_normal(t_obj *sphere, float3 hit_pos)
{
	return (normalize(hit_pos - sphere->s_center));
}

static	float3	get_plane_normal(t_obj *plane)
{
	return (normalize(plane->p_normal));
}

static	float3	get_normal(t_obj *object, float3 hit_pos)
{
	float3 normal;

	if (object->type == 0)
		normal = get_sphere_normal(object, hit_pos);
	if (object->type == 1)
		normal = get_plane_normal(object);

	return (normal);
}
static		bool		intersect(float3 orig, float3 dir, __global t_obj* objects, float3 *hit_pos, float3 *N, float4 *color, int *id)
{
	float	closest_dist = FLT_MAX;
	float	dist_i;

	for(int i = 0; i < 4; i++)
	{
		t_obj object = objects[i];
		if (object.type == 0)
			dist_i = intersect_sphere(&object, orig, dir);
		if (object.type == 1)
			dist_i = intersect_plane(&object, orig, dir);
		if (object.type == 2)
			dist_i = intersect_cone(&object, orig, dir);

		if (dist_i != 0.0f && dist_i < closest_dist)
		{
			closest_dist = dist_i;
			*hit_pos = orig + dir * dist_i;
			*N = get_normal(&object, *hit_pos);
			*color = object.material.diff_color;
			*id = i;
		}
	}
	return (closest_dist < 100);
}

static	float  get_light(float3 L, float3 N, t_light light)
{
	float	df_light_int = 0.0f;

	float dot_light_dir = dot(N, L);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(L));
	return(df_light_int);
}

static	float3	get_light_dir(float3 hit_pos, t_light light)
{
	float3	light_dir;
	if (light.type == 2)
		light_dir = (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_pos;
	if (light.type == 3)
		light_dir = light.dir;
	return (light_dir);
}

static	bool	shadow_intersect(float3 orig, float3 dir, __global t_obj* objects, float3 *hit_pos, float3 *N)
{
	float	closest_dist = FLT_MAX;
	float	dist_i;

	for(int i = 0; i < 4; i++)
	{
		t_obj object = objects[i];
		if (object.type == 0)
			dist_i = intersect_sphere(&object, orig, dir);
		if (object.type == 1)
			dist_i = intersect_plane(&object, orig, dir);
		if (object.type == 2)
        	dist_i = intersect_cone(&object, orig, dir);

		if (dist_i != 0.0f && dist_i < closest_dist)
		{
			closest_dist = dist_i;
			*hit_pos = orig + dir * dist_i;
			*N = get_normal(&object, *hit_pos);;
		}
	}
	return (closest_dist < 100);
}

static		float3 reflect_ray(float3 R, float3 N)
{
	return (2 * N * dot(N, R) - R);
}

static		float4 clamp_color(float4 color)
{
	float4 res;

	res.x = color.x > 255.0f ? 255.0f : color.x;
	res.y = color.y > 255.0f ? 255.0f : color.y;
	res.z = color.z > 255.0f ? 255.0f : color.z;
	res.w = color.w > 255.0f ? 255.0f : color.w;
	return (res);
}

static	float4	trace(float3 orig, float3 dir, __global t_obj *objects, __global t_light *lights, int depth)
{
	float3	hit_pos, N;
	int		id = -1;
	float	prev_reflection = 0.0f;
	float3	shadow_hit_pos, shadow_N;
	float4	color, acum_color;
	float3	light_dir;
	float	intensity = 0;


	acum_color = 0.0f;
	prev_reflection = 0.0f;
	for (int i = 0; i < depth; i++)
	{
		if (!intersect(orig, dir, objects, &hit_pos, &N, &color, &id))
        		return (clamp_color(acum_color + (float4)(55.0f, 55.0f, 55.0f, 0.0f)));
        for (int i = 0; i < 3; i++)
		{
			if (lights[i].type == 1)
				intensity += lights[i].intensity;
			else
			{
				light_dir = get_light_dir(hit_pos, lights[i]);
				if (shadow_intersect(hit_pos, light_dir, objects, &shadow_hit_pos, &shadow_N))
					continue;
				intensity += get_light(light_dir, N, lights[i]);
				if (objects[id].material.specular > 0)
				{
					float3 R = 2 * N * dot(N, light_dir) - light_dir;
					float r_dot_dir = dot(R, -dir);
					if (r_dot_dir > 0)
						intensity += lights[i].intensity * pow(r_dot_dir / (length(R) * length(dir)), objects[id].material.specular);
				}
			}
		}
		intensity = intensity > 1 ? 1 : intensity;
		color = color * intensity;
		if (objects[id].material.reflection == 0 || depth == 1)
			return (color);
		acum_color += color * (1 - objects[id].material.reflection) + color * prev_reflection;
		dir = reflect_ray(-dir, N);
        orig = hit_pos + N * 0.001f;
        prev_reflection = objects[id].material.reflection;
	}
	return (clamp_color(acum_color));
}

__kernel void raytrace(t_camera camera, __global t_obj* objects, __global float* randoms, int samples, __global t_light *lights, __global float4* output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
 	int width = get_global_size(0);
	int height = get_global_size(1);
	float Px, Py;
	float3 dir;
	if (x == width/ 2 && y == height / 2)
			printf("\n");

    /* 0 sample */
	Px = (float)x / (width - 1);
	Py = (float)y / (height - 1);
	dir = camera.upper_left_corner + Px * camera.horizontal - Py * camera.vertical - camera.origin;
	dir = normalize(dir);
	output[y * width + x] = trace(camera.origin, dir, objects, lights, 1);

	if (samples > 1)
	{
		for (int i = 0; i < samples; i++)
		{
			Px = ((float)x + randoms[(y * width + x) * samples + i]) / (width - 1);
			Py = ((float)y + randoms[(y * width + x) * samples + i]) / (height - 1);
			dir = camera.upper_left_corner + Px * camera.horizontal - Py * camera.vertical - camera.origin;
			dir = normalize(dir);
			output[y * width + x] += trace(camera.origin, dir, objects, lights, 1);
		}
	}

	/* is there is only one sample we do not need to divide the color */
	output[y * width + x] /= samples == 1 ? 1 : samples + 1;
}

