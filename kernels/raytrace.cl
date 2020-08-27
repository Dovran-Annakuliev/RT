typedef struct			s_vector3
{
	float x;
	float y;
	float z;
}						t_vector3;

t_vector3				new_vector3(float x, float y, float z);

typedef struct		s_sphere
{
	t_vector3		c;
	float			r;
}					t_sphere;

t_sphere			new_sphere(t_vector3 center, float radius);

__kernel void raytrace(t_vector3 o, t_vector3 d, t_sphere s, __global int *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);

    float3 orig = (float3)(o.x, o.y, o.z);
    float3 dir = (float3)(d.x, d.y, d.z);
    float3 center = (float3)(s.c.x, s.c.y, s.c.z);
    float radius = (float)(s.r);
    float3 intersection;

    float3 v_orig_center = center - orig;
    if (dot(v_orig_center, dir) < 0)
    {
    	if (length(v_orig_center) > r)
    		;
    	else if (length(v_orig_center) == r)
    		intersection = orig;
    }
    else
    {

    }


	output[y * width + x] = (y * width + x) / (width / height) * 255;
}
