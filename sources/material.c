#include "../includes/material.h"

t_material		new_material(t_vector3 color)
{
	t_material res;
	res.diff_color = color;
	return res;
}
