__kernel	void		raytrace(__global int *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);

	output[y * width + x] = 255;
}
