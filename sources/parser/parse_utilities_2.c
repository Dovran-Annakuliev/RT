#include "../../includes/rtv1.h"

void	clamp_color(cl_float4 *color)
{
	color->x = color->x > 255.0f ? 255.0f : color->x;
	color->y = color->y > 255.0f ? 255.0f : color->y;
	color->z = color->z > 255.0f ? 255.0f : color->z;
	color->w = color->w > 255.0f ? 255.0f : color->w;
}
