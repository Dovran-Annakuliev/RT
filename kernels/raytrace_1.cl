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
	int					type;
    float3			    s_center;
    float			    s_radius;
    float3			    p_pos;
    float3 			    p_normal;
    float3			    cone_pos;
    float			    cone_angle;
    float3  			cone_axis;
    float3	    		cyl_pos;
    float		    	cyl_r;
    float3			    cyl_axis;
    float3	    		tr_0;
    float3		    	tr_1;
    float3			    tr_2;
    float3  			tr_normal;
    int		    		tr_or;
    float3	    		rec_0;
    float3	    		rec_1;
    float3	    		rec_2;
    float3	    		rec_3;
    float3	    		crcl_pos;
    float3	    		crcl_normal;
    float	    		crcl_r;
    t_material			material;
}						t_obj;

typedef struct		s_light
{
	int				type;
	float3			pos;
	float3			dir;
	float		    r;
    float4		    clr;
    float		    width;
    float		    height;
    float3		    normal;
	float			intensity;
}					t_light;


typedef	struct	s_ray
{
	float3		orig;
	float3		dir;
	float		t;
	int			inside;
}				t_ray;

static	t_ray	new_ray(float3 orig, float3 dir)
{
	t_ray r;

	r.orig = orig;
	r.dir = dir;
	r.t = 0.0f;
	r.inside = 0;
	return (r);
}

typedef struct	s_hit_record
{
	t_ray		ray;
	float3		hit_point;
	float3		N;
	int			id;
}				hit_record;

static	float		solve_eq(float a, float b, float c, float t_min, float t_max, int *inside)
{
	float dis = b * b - 4 * a * c;
	if (dis < 0.0f)
		return (0.0f);
	dis = sqrt(dis);
	float x1 = (-b - dis) / (2 * a);
	float x2 = (-b + dis) / (2 * a);
	if (x1 < 0 && x2 > t_min)
		*inside = 1;
	if (x2 < 0 && x1 > t_min)
		*inside = 1;
	if (x1 > t_min && x2 > t_min)
		return (x1 <= x2 ? x1 : x2);
	if (x1 > t_min || x2 > t_min)
		return (x1 <= x2 ? x2 : x1);
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

	dist = solve_eq(a, b, c, 0.001f, ray->t, &ray->inside);
	return (dist);
}

static	float	intersect_plane(t_obj *plane, t_ray *ray)
{
	float dist;

	float a = dot(plane->p_normal, ray->dir);
	if (fabs(a) < 0.001f)
		return (0);
	float b = dot(plane->p_pos - ray->orig, plane->p_normal) / a;
	dist = b < 0.001f ? 0 : b;

	float3 hit_point = ray->orig + ray->dir * dist;
	return (dist);
}

/*
static float intersect_rectangle(t_obj *rect, t_ray *ray)
{
    float dist = intersect_plane(rect, ray);
    float v1 = ;
    float v2 = ;
    float v3 = rect->p4 - rect->p3;
    float v4 = rect->p4 - rect->p3;
    float v5 = rect->p4 - rect->p3;
}
*/

static float		intersect_triangle(t_obj *triangle,  t_ray *ray)
{
    float EPS = 0.00001f;
    float3 e1 = triangle->tr_1 - triangle->tr_0;
    float3 e2 = triangle->tr_2 - triangle->tr_0;
    float3 pvec = cross(ray->dir, e2);
    float det = dot(e1, pvec);

    if (det < EPS && det > -EPS) {
        return 0;
    }

    float inv_det = 1 / det;
    float3 tvec = ray->orig - triangle->tr_0;
    float u = dot(tvec, pvec) * inv_det;
    if (u < 0 || u > 1) {
        return (0);
    }

    float3 qvec = cross(tvec, e1);
    float v = dot(ray->dir, qvec) * inv_det;
    if (v < 0 || u + v > 1) {
        return (0);
    }
    return (dot(e2, qvec) * inv_det);
}


static	float	intersect_cone(t_obj *cone, t_ray *ray)
{
	float dist;

	float a;
	float b;
	float c;
	float angle = tan(cone->cone_angle * M_PI_F / 180);
	float temp = 1 + angle * angle;

	float3 x = ray->orig - cone->cone_pos;
	float d_v = dot(ray->dir, cone->cone_axis);
	float x_v = dot(x, cone->cone_axis);
	a = dot(ray->dir, ray->dir) - temp * d_v * d_v;
	b = 2 * (dot(ray->dir, x) - temp * d_v * x_v);
	c = dot(x, x) - temp * x_v * x_v;
	dist = solve_eq(a, b, c, 0.001f, ray->t, &ray->inside);
	return (dist);
}

static	float	intersect_cylinder(t_obj *cyl, t_ray *ray)
{
	float dist;

    float a;
    float b;
    float c;

    float3 x = ray->orig - cyl->cyl_pos;
    float d_v = dot(ray->dir, cyl->cyl_axis);
    float x_v = dot(x, cyl->cyl_axis);

    a = dot(ray->dir, ray->dir) - d_v * d_v;
    b = 2 * (dot(ray->dir, x) - d_v * x_v);
    c = dot(x, x) - x_v * x_v - cyl->cyl_r * cyl->cyl_r;
    dist = solve_eq(a, b, c, 0.001f, ray->t, &ray->inside);
    return (dist);
}

static	float3	get_sphere_normal(t_obj *sphere, float3 hit_pos)
{
	return (normalize(hit_pos - sphere->s_center));
}

static	float3	get_plane_normal(t_obj *plane, t_ray *ray)
{
	float d = dot(plane->p_normal, ray->dir);
	if (0.001f < d)
		return (normalize(plane->p_normal * -1.0f));
	return (normalize(plane->p_normal));
}

static	float3	get_cone_normal(t_obj *cone, float3 hit_pos, t_ray *ray)
{
	float3 cp = hit_pos - cone->cone_pos;
	float angle = tan(cone->cone_angle * M_PI_F / 180);
    float temp = 1 + angle * angle;
	float3 scaled_axis = cone->cone_axis * temp;
	float dir_dot_axis = dot(ray->dir, cone->cone_axis);
	float k = dir_dot_axis * ray->t + dot(ray->orig - cone->cone_pos, cone->cone_axis);

	float3 res = cp - scaled_axis * k;
	return (normalize(res));
}

static float3	get_cylinder_normal(t_obj *cyl, float3 hit_pos, t_ray *ray)
{
	float3 res;

	float3 cp = hit_pos - cyl->cyl_pos;
	float3 x = ray->orig - cyl->cyl_pos;
	float d_v = dot(ray->dir, cyl->cyl_axis);
	float x_v = dot(x, cyl->cyl_axis);
	float m = d_v * ray->t + x_v;
	res = cp - cyl->cyl_axis * m;

	return (normalize(res));
}

static	float3	get_normal(t_obj *object, hit_record hit, t_ray *ray)
{
	float3 normal;

	if (object->type == 0)
		normal = get_sphere_normal(object, hit.hit_point);
	if (object->type == 1)
		normal = get_plane_normal(object, ray);
	if (object->type == 2)
		normal = get_cone_normal(object, hit.hit_point, ray);
	if (object->type == 3)
		normal = get_cylinder_normal(object, hit.hit_point, ray);
    if (object->type == 4)
    {
        normal = object->tr_normal;
        /*
        if (dot(ray->dir, normal) > 0)
            normal = normal * -1;
        */
    }
	return (normal);
}


static	float  get_light(float3 L, float3 N, t_light light)
{
	float	df_light_int = 0.0f;

	float dot_light_dir = dot(N, L);

    float r2 = length(L);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(L));
	return(df_light_int);
}

static	float3	get_light_dir(float3 hit_point, t_light light)
{
	float3	light_dir;

    if (light.type == 1)
        light_dir = -light.dir;
	if (light.type == 2)
		light_dir = (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_point;
	return (light_dir);
}


static		bool		intersect(t_ray *ray, hit_record *hit, __global t_obj* objects, int obj_n)
{
	float	dist_i = 0.0f;
	ray->t = FLT_MAX;

	for (int i = 0; i < obj_n; i++)
	{
		t_obj object = objects[i];

		if (object.type == 0)
			dist_i = intersect_sphere(&object, ray);
		if (object.type == 1)
			dist_i = intersect_plane(&object, ray);
		if (object.type == 2)
			dist_i = intersect_cone(&object, ray);
		if (object.type == 3)
			dist_i = intersect_cylinder(&object, ray);
		if (object.type == 4)
            dist_i = intersect_triangle(&object, ray);

		if (dist_i != 0.0f && dist_i < ray->t && dist_i > 0.001f && dist_i < FLT_MAX)
		{
			ray->t = dist_i;
			hit->id = i;
		}
	}
	return (ray->t < 1000);
}

static	bool	shadow_intersect(t_ray *ray, __global t_obj* objects, float	min_v, float max_v, int obj_n)
{
	float	dist_i = 0;
    ray->t = FLT_MAX;

	for(int i = 0; i < obj_n; i++)
	{
		t_obj object = objects[i];
		if (object.type == 0)
			dist_i = intersect_sphere(&object, ray);
		if (object.type == 1)
			dist_i = intersect_plane(&object, ray);
		if (object.type == 2)
			dist_i = intersect_cone(&object, ray);
		if (object.type == 3)
			dist_i = intersect_cylinder(&object, ray);
		if (object.type == 4)
            dist_i = intersect_triangle(&object, ray);

		if (dist_i != 0.0f && dist_i < ray->t && dist_i > min_v && dist_i < max_v)
		{
			ray->t = dist_i;
			return (ray->t < max_v);
		}
	}
	return (ray->t < max_v);
}

static	float4	trace(t_ray *ray, __global t_obj *objects, __global t_light *lights, int obj_n, int lights_n)
{
	hit_record hit;
	float4	color;
	float3	light_dir;
	float	intensity = 0;
	float4  bg_color = (float4)(55.0f, 55.0f, 55.0f, 0.0f);

	if (!intersect(ray, &hit, objects, obj_n))
		return (bg_color);
	t_obj object_hit = objects[hit.id];
	hit.hit_point = ray->orig + ray->dir * ray->t;
	hit.N = get_normal(&object_hit, hit, ray);
	for (int i = 0; i < lights_n; i++)
	{
		if (lights[i].type == 0)
			intensity += lights[i].intensity;
		else if (!ray->inside)
		{
			light_dir = get_light_dir(hit.hit_point, lights[i]);
			t_ray shadow_ray = new_ray(hit.hit_point + hit.N * 0.001f, light_dir);
			if (shadow_intersect(&shadow_ray, objects, 0.001f, lights[i].type == 1 ? FLT_MAX : 1.0f, obj_n))
				continue;

		    intensity += get_light(light_dir, hit.N, lights[i]);
			if (object_hit.material.specular > 0)
			{
				float3 R = 2 * hit.N * dot(hit.N, light_dir) - light_dir;
				float r_dot_dir = dot(R, ray->dir * -1.0f);
				if (r_dot_dir > 0)
				intensity += lights[i].intensity * pow(r_dot_dir / (length(R) * length(ray->dir)), object_hit.material.specular);
			}
		}
	}
	intensity = intensity > 1 ? 1 : intensity;
	color = object_hit.material.diff_color * intensity;
	return (clamp(color, (float4)(0.0f, 0.0f, 0.0f, 0.0f), (float4)(255.0f, 255.0f, 255.0f, 255.0f)));
}

__kernel void raytrace(t_camera camera, __global t_obj* objects, __global float* randoms, int samples, __global t_light *lights, __global float4* output, int	obj_n, int lights_n)
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
	output[y * width + x] = trace(&ray, objects, lights, obj_n, lights_n);


    int n = 4;
	for (int i = 0; i < n; i++)
	{
	    for (int j = 0; j < n; j++)
        {
    			Px = ((float)x + (i + 0.5) / n) / (width - 1);
    			Py = ((float)y + (j + 0.5) / n) / (height - 1);
    			dir = camera.upper_left_corner + Px * camera.horizontal - Py * camera.vertical - camera.origin;
    			dir = normalize(dir);
    			t_ray ray = new_ray(camera.origin, dir);
    			output[y * width + x] += trace(&ray, objects, lights, obj_n, lights_n);
        }
    }
    output[y * width + x] = clamp(output[y * width + x] / (n * n), (float4)(0.0f, 0.0f, 0.0f, 0.0f), (float4)(255.0f, 255.0f, 255.0f, 255.0f));


}

static		float3 reflect_ray(float3 R, float3 N)
{
	return (2 * N * dot(N, R) - R);
	/* maybe R - 2 * N * dot (N, R) */
}
