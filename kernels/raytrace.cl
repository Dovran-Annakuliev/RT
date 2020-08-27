static void change_places(float &x0, float &x1)
{
	float temp;

	temp = x0;
	x0 = x1;
	x1 = temp;
}

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

static	int				solve_eq(float a, float b, float c, float &x0, float &x1)
{
	float dis = b * b - 4 * a * c;
	if (dis < 0)
		return (0);
	else if (dis == 0)
	{
		x0 = -0.5 * b / a;
		x1 = -0.5 * b / a;
	}
	else
	{
		float s = (b > 0) ? -0.5 * (b + sqrt(dis)) : -0.5 * (b - sqrt(dis));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1)
		change_places(x0, x1);
	return (1);
}

__kernel void raytrace(t_vector3 o, t_vector3 d, t_sphere s, __global int *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);

	float t0, t1, t;

    float3 orig = (float3)(o.x, o.y, o.z);
    float3 dir = (float3)(d.x, d.y, d.z);
    float3 center = (float3)(s.c.x, s.c.y, s.c.z);
    float radius = (float)(s.r);

    float3 L = orig - center;
    float a = dot(dir, dir);
    float b = 2 * dot(dir, L);
    float c = dot(L, L) - radius * radius;
    if (!(solve_eq(a, b, c, t0, t1)))
    	output[y * width + x] = 0;
    else
    {
    	if (t0 > t1){
    		change_places(t0, t1);
    	}
    	if (t0 < 0)
    	{
    		t0 = t1;
    		if (t0 < 0){
    			output[y * width + x] = 0;
			}
		}
		t = t0;
		output[y * width + x] = 1;
	}
}
