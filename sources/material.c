#include "../includes/material.h"


t_material		new_material(cl_float4 color, float specular, float reflection)
{
	t_material res;
	res.diff_color = color;
	res.specular = specular;
	res.reflection = reflection;
	return res;
}
