typedef struct			s_vector3
{
	float x;
	float y;
	float z;
}						t_vector3;

typedef struct	s_material
{
	t_vector3	diff_color;
}				t_material;

typedef struct		s_sphere
{
	t_vector3		c;
	float			r;
	t_material		material;
}					t_sphere;

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

static		int		sphere_intersect(float3 orig, float3 dir, t_sphere s)
{
	float	t0, t1, t;
	float	dist = FLT_MAX;
	t = dist;

	float3	hit_pos, N;
	float3 center = (float3)(s.c.x, s.c.y, s.c.z);
	float radius = (float)(s.r);
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
		t = t0;
		hit_pos = orig - dir * t;
		N = normalize(hit_pos - center);
		return(1);
		}
	else
		return (0);
}

__kernel void raytrace(float fov, t_sphere s, __global float4* output)
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

	if (sphere_intersect(orig, dir, s))
		output[y * width + x] = (float4)(s.material.diff_color.x, s.material.diff_color.y, s.material.diff_color.z, 0.0f);
	else
		output[y * width + x] = (float4)(25.0f, 25.0f, 25.0f, 0.0f);
}
