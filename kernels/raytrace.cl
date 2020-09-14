typedef struct	s_material
{
	float4		diff_color;
	float		specular;
	float		reflection;
}				t_material;

typedef	struct	s_ray
{
	float3		orig;
	float3		dir;
	float		t;
}				t_ray;

static	t_ray	new_ray(float3 orig, float3 dir)
{
	t_ray r;

	r.orig = orig;
	r.dir = dir;
	return (r);
}

typedef struct	s_hit_record
{
	t_ray		ray;
	float3		hit_point;
	float3		N;
	int			id;
}				hit_record;

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

static		float4 clamp_color(float4 color);

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

static	float	intersect_sphere(t_obj	*sphere, t_ray *ray)
{
	float dist;

	float3 center = (float3)(sphere->s_center.x, sphere->s_center.y, sphere->s_center.z);
	float radius = (float)(sphere->s_radius);

	float3 L = ray->orig - center;
	float a = dot(ray->dir, ray->dir);
	float b = 2 * dot(L, ray->dir);
	float c = dot(L, L) - radius * radius;

	dist = solve_eq(a, b, c, 0.001f, FLT_MAX);
	return (dist);
}

static	float	intersect_plane(t_obj	*plane, t_ray *ray)
{
	float dist;

	float a = dot(plane->p_normal, ray->dir);
	if (fabs(a) < 0.001f)
		return (0);
	float b = -(dot(ray->orig - plane->p_pos, plane->p_normal)) / a;
	dist = b < 0.001f ? 0 : b;
	return (dist);
}


/*
float	temp = 1 + k * k;
float a = dot(dir, dir) - temp * d_v * d_v;
float b = 2.0 * (dot(dir, X) - temp * d_v * x_v);
float c = dot(X,X) - temp * x_v * x_v;

dist = solve_eq(a, b, c, 0.001f, FLT_MAX);
float3 hit_point = orig + dir * dist;
if (dot(cone->cone_axis, hit_point) < 0)
	return (0.0f);
return (dist);
*/

static	float	intersect_cone(t_obj	*cone, t_ray *ray)
{
	float dist;

	float3	X = ray->orig - cone->cone_pos;
	float	d_v = dot(ray->dir, cone->cone_axis);
	float	x_v = dot(X, cone->cone_axis);
	float	k = cos(cone->cone_angle * M_PI_F / 180);
	float	angle2 = k * k;

	float a = d_v * d_v - angle2;
	float b = 2.0f * (d_v * x_v - dot(ray->dir, X) * angle2);
	float c = x_v * x_v - dot(X, X) * angle2;
	dist = solve_eq(a, b, c, 0.001f, FLT_MAX);
	float3 cp = ray->orig + ray->dir * dist - cone->cone_pos;
	float h = dot(cp, cone->cone_axis);
    if (h < 0 || h > 3)
    	return (0.0f);
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

static	float3	get_cone_normal(t_obj *cone, float3 hit_pos, t_ray *ray)
{
	/*
	float3	pos_to_hitpoint;
	float3	X = orig - cone->cone_pos;
	float	d_v = dot(dir, cone->cone_axis);
	float	x_v = dot(X, cone->cone_axis);
	float	m = d_v * t + x_v;
	*hit_pos = cone->cone_pos + cone->cone_axis * m;
	pos_to_hitpoint = *hit_pos - cone->cone_pos;

	float	k = tan(cone->cone_angle * M_PI_F / 180);
	float	a = m * k * k;
	return (normalize(pos_to_hitpoint - (1 + k * k) * cone->cone_axis * m));
	*/
	/*
	float3 c_to_p = hit_pos - cone->cone_pos;
	float3 tangent = cross(c_to_p, cone->cone_axis);
	float3 res = cross(tangent, c_to_p);
	return (normalize(res));
	*/

	float3 cp = hit_pos - cone->cone_pos;
	float axis_dot_cp = dot(cone->cone_axis, cp);
	float cp2 = dot(cp, cp);
	float3 normal = normalize(cp * (axis_dot_cp / cp2) - cone->cone_axis);
}

static	float3	get_normal(t_obj *object, hit_record hit, t_ray *ray)
{
	float3 normal;

	if (object->type == 0)
		normal = get_sphere_normal(object, hit.hit_point);
	if (object->type == 1)
		normal = get_plane_normal(object);
	if (object->type == 2)
        normal = get_cone_normal(object, hit.hit_point, ray);
	return (normal);
}

static	float  get_light(float3 L, float3 N, t_light light)
{
	float	df_light_int = 0.0f;

	float dot_light_dir = dot(N, L);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(L));
	return(df_light_int);
}

static	float3	get_light_dir(float3 hit_point, t_light light)
{
	float3	light_dir;
	if (light.type == 2)
		light_dir = (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_point;
	if (light.type == 3)
		light_dir = light.dir;
	return (light_dir);
}

static		bool		intersect(t_ray *ray, hit_record *hit, __global t_obj* objects)
{
	float	dist_i;
	ray->t = FLT_MAX;

	for(int i = 0; i < 4; i++)
	{
		t_obj object = objects[i];
		if (object.type == 0)
			dist_i = intersect_sphere(&object, ray);
		if (object.type == 1)
			dist_i = intersect_plane(&object, ray);
		if (object.type == 2)
			dist_i = intersect_cone(&object, ray);

		if (dist_i != 0.0f && dist_i < ray->t)
		{
			ray->t = dist_i;
			hit->id = i;
		}
	}
	return (ray->t < 100);
}

static	bool	shadow_intersect(t_ray *ray, __global t_obj* objects)
{
	float	closest_dist = FLT_MAX;
	float	dist_i = 0;

	for(int i = 0; i < 4; i++)
	{
		t_obj object = objects[i];
		if (object.type == 0)
			dist_i = intersect_sphere(&object, ray);
		if (object.type == 1)
			dist_i = intersect_plane(&object, ray);
		if (object.type == 2)
			dist_i = intersect_cone(&object, ray);

		if (dist_i != 0.0f && dist_i < closest_dist)
		{
			closest_dist = dist_i;
			return (closest_dist < 100);
		}
	}
	return (closest_dist < 100);
}

static	float4	trace(t_ray *ray, __global t_obj *objects, __global t_light *lights)
{
	hit_record hit;
	float4	color;
	float3	light_dir;
	float	intensity = 0;


	if (!intersect(ray, &hit, objects))
		return ((float4)(55.0f, 55.0f, 55.0f, 0.0f));
	t_obj object_hit = objects[hit.id];
	hit.hit_point = ray->orig + ray->dir * ray->t;
	hit.N = get_normal(&object_hit, hit, ray);
	for (int i = 0; i < 3; i++)
	{
		if (lights[i].type == 1)
			intensity += lights[i].intensity;
		else
		{
			light_dir = get_light_dir(hit.hit_point, lights[i]);
			/*
			if (shadow_intersect(hit.hit_point + N * 0.0001f, light_dir, objects))
				continue;
			*/
			intensity += get_light(light_dir, hit.N, lights[i]);
			if (object_hit.material.specular > 0)
			{
				float3 R = 2 * hit.N * dot(hit.N, light_dir) - light_dir;
				float r_dot_dir = dot(R, -ray->dir);
				if (r_dot_dir > 0)
					intensity += lights[i].intensity * pow(r_dot_dir / (length(R) * length(ray->dir)), object_hit.material.specular);
			}
		}
	}
	intensity = intensity > 1 ? 1 : intensity;
	color = object_hit.material.diff_color * intensity;
	return (clamp_color(color));
}

__kernel void raytrace(t_camera camera, __global t_obj* objects, __global float* randoms, int samples, __global t_light *lights, __global float4* output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
 	int width = get_global_size(0);
	int height = get_global_size(1);
	float Px, Py;
	float3 dir;

    /* 0 sample */
	Px = (float)x / (width - 1);
	Py = (float)y / (height - 1);
	dir = camera.upper_left_corner + Px * camera.horizontal - Py * camera.vertical - camera.origin;
	dir = normalize(dir);
	t_ray ray = new_ray(camera.origin, dir);
	output[y * width + x] = trace(&ray, objects, lights);

	if (samples > 1)
	{
		for (int i = 0; i < samples; i++)
		{
			Px = ((float)x + randoms[(y * width + x) * samples + i]) / (width - 1);
			Py = ((float)y + randoms[(y * width + x) * samples + i]) / (height - 1);
			dir = camera.upper_left_corner + Px * camera.horizontal - Py * camera.vertical - camera.origin;
			dir = normalize(dir);
			t_ray ray = new_ray(camera.origin, dir);
			output[y * width + x] += trace(&ray, objects, lights);
		}
	}

	/* is there is only one sample we do not need to divide the color */
	output[y * width + x] /= samples == 1 ? 1 : samples + 1;
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

static		float3 reflect_ray(float3 R, float3 N)
{
	return (2 * N * dot(N, R) - R);
	/* maybe R - 2 * N * dot (N, R) */
}
