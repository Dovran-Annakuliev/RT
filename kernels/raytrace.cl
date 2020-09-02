typedef struct			s_vector3
{
	float x;
	float y;
	float z;
}						t_vector3;

typedef struct	s_material
{
	float4		diff_color;
}				t_material;

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
	t_vector3		pos;
	float			intensity;
}					t_light;

static void change_places(float *x0, float *x1)
{
	float temp;

	temp = *x0;
	*x0 = *x1;
	*x1 = temp;
}

static	int			solve_eq(float a, float b, float c, float *x0, float *x1)
{
	float dis = b * b - 4 * a * c;
	if (dis < 0)
		return (0);
	else if (dis == 0)
	{
		*x0 = -0.5 * b / a;
		*x1 = -0.5 * b / a;
	}
	else
	{
		float q = (b > 0) ? -0.5 * (b + sqrt(dis)) : -0.5 * (b - sqrt(dis));
		*x0 = q / a;
		*x1 = c / q;
	}
	if ((*x0) > (*x1))
		change_places(x0, x1);
	return (1);
}

static		bool		sphere_intersect(float3 orig, float3 dir, __global t_obj* objects, float3 *hit_pos, float3 *N, float4 *color)
{
	float	t0, t1;
	float	spheres_dist = FLT_MAX;

	for(int i = 0; i < 3; i++)
	{
		float	dist_i;

		float3 center = (float3)(objects[i].s_center.x, objects[i].s_center.y, objects[i].s_center.z);
		float radius = (float)(objects[i].s_radius);
		float3 L = orig - center;
		float a = dot(dir, dir);
		float b = 2 * dot(dir, L);
		float c = dot(L, L) - radius * radius;

		if (solve_eq(a, b, c, &t0, &t1))
		{
			if (t0 > t1)
				change_places(&t0, &t1);
			if (t0 < 0)
			{
				t0 = t1;
				if (t0 < 0)
					return (0);
			}
			dist_i = t0;
			if (dist_i < spheres_dist)
			{
				spheres_dist = dist_i;
				*hit_pos = orig - dir * dist_i;
				*N = normalize(*hit_pos - center);
				*color = objects[i].material.diff_color;
			}
		}
	}
	return (spheres_dist < 1000);
}

static	float4	trace(float3 orig, float3 dir, __global t_obj *objects, t_light light)
{
	float3	hit_pos, N;
	float4	color;

	if (!sphere_intersect(orig, dir, objects, &hit_pos, &N, &color))
		return((float4)(0.0f, 0.0f, 0.0f, 0.0f));
	float	df_light_int = 0.0f;
	float3	light_dir = (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_pos;
	float dot_light_dir = dot(N, light_dir);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(light_dir));
	return(color);
}

__kernel void raytrace(float fov, __global t_obj* objects, t_light light, __global float4* output)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);

	float imageAspectRatio = width / (float)height;
	float scale = tan(fov / 2 * M_PI_F / 180);

    float Px = (2 * (x + 0.5) / width - 1) * scale * imageAspectRatio;
    float Py = (1 - 2 * (y + 0.5) / height) * scale;


    float3 orig = (float3)(0, 0, 0);
    float3 dir = (float3)(Px, Py, -1) - orig;
    dir = normalize(dir);

	output[y * width + x] = trace(orig, dir, objects, light);
}
