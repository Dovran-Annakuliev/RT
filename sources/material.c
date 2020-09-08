#include "../includes/material.h"


t_material		new_material(cl_float4 color, float specular)
{
	t_material res;
	res.diff_color = color;
	res.specular = specular;
	return res;
}
