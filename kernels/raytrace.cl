#include "../includes.h/vectors"
#include "../includes.h/rgba.h"

__kernel	void		raytrace(t_vector orig, t_vector dir, __global t_rgba *output)
{
	int x = get_global_id(0);
    int y = get_global_id(1);
    int width = get_global_size(0);
    int height = get_global_size(1);

    float3 orig = (float3)(orig.x, orig.y, orig.z);
    float3 dir = (float3)(dir.x, dir.y, dir.z);

	output[y * width + x] = new_rgb_color(255, 0, 0, 0);
}
