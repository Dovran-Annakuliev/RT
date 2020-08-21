typedef struct			s_vector3
{
	float x;
	float y;
	float z;
}						t_vector3;

t_vector3				new_vector3(float x, float y, float z);

__kernel void raytrace(t_vector3 orig, t_vector3 dir, __global int *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);

	output[y * width + x] = (y * width + x) / (width / height) * 255;
}
