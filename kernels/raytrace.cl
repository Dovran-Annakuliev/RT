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

static	float		solve_eq(float a, float b, float c)
{
	float dis = b * b - 4 * a * c;
	if (dis < 0.0f)
		return (0.0f);
	dis = sqrt(dis);
	float x1 = (-b - dis) * (1 / (2 * a));
	float x2 = (-b + dis) * (1 / (2 * a));
	if (x1 > 0.001f && x2 > 0.001f)
		return x1 <= x2 ? x1 : x2;
	if (x1 > 0.001f || x2 > 0.001f)
		return x1 <= x2 ? x2 : x1;
	return (0.f);
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
		float a = 1;
		float b = 2 * dot(L, dir);
		float c = dot(L, L) - radius * radius;
		dist_i = solve_eq(a, b, c);

		if (dist_i != 0.0f && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			*hit_pos = orig + dir * dist_i;
			*N = normalize(*hit_pos - center);
			*color = objects[i].material.diff_color;
		}
	}
	return (spheres_dist < 1000);
}

static	float4	trace(float3 orig, float3 dir, __global t_obj *objects, t_light light)
{
	float3	hit_pos, N;
	float4	color;

	if (!sphere_intersect(orig, dir, objects, &hit_pos, &N, &color))
		return((float4)(100.0f, 100.0f, 100.0f, 0.0f));
	float	df_light_int = 0.0f;
	float3	light_dir = (float3)(light.pos.x, light.pos.y, light.pos.z) - hit_pos;
	float dot_light_dir = dot(N, light_dir);
	if (dot_light_dir > 0)
		df_light_int += light.intensity * dot_light_dir / (length(N) * length(light_dir));
	return(color * df_light_int);
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
	float Py = 1 - (2 * (y + 0.5) / height) * scale;


	/*float Px = x - width / 2;*/
	/*float Py = height / 2 - y;*/
	/*float Pz = -(height / 2) / tan(fov / 2  * M_PI_F/ 180);*/


	float3 orig = (float3)(0, 0, 0);

	float3 dir = (float3)(Px, Py, -1);
	dir = dir - orig;
	dir = normalize(dir);
	output[y * width + x] = trace(orig, dir, objects, light);
}
