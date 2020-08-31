typedef struct			s_vector3
{
	float x;
	float y;
	float z;
}						t_vector3;

typedef struct		s_sphere
{
	t_vector3		c;
	float			r;
}					t_sphere;

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

__kernel void raytrace(int imageWidth, int imageHeight, float fov, t_sphere s, __global int *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);

	float t0, t1, t;
	float imageAspectRatio = imageWidth / (float)imageHeight;
	float scale = tan(fov / 2 * M_PI_F / 180);
    float Px = (2 * (x + 0.5) / imageWidth - 1) * scale * imageAspectRatio;
    float Py = (1 - 2 * (y + 0.5) / imageHeight) * scale;
    float3 orig = (float3)(0, 0, 0);
    float3 dir = (float3)(Px, Py, -1) - orig;
    dir = normalize(dir);
    float3 center = (float3)(s.c.x, s.c.y, s.c.z);
    float radius = (float)(s.r);

    float3 L = orig - center;
    float a = dot(dir, dir);
    float b = 2 * dot(dir, L);
    float c = dot(L, L) - radius * radius;
    if (!(solve_eq(a, b, c, &t0, &t1)))
    	output[y * width + x] = 0;
    else
    {
    	if (t0 > t1)
    		change_places(&t0, &t1);
    	if (t0 < 0)
    	{
    		t0 = t1;
    		if (t0 < 0)
    			output[y * width + x] = 0;
    		else
    			output[y * width + x] = 1;
		}
		else
		{
			t = t0;
			output[y * width + x] = 1;
		}
	}
}
