#include "../includes/material.h"


t_material		new_material(cl_float4 color)
{
	t_material res;
	res.diff_color = color;
	return res;
}
