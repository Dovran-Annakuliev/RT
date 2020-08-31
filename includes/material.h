#ifndef MATERIAL_H
#define MATERIAL_H

#include "vectors.h"

typedef struct	s_material
{
	t_vector3	diff_color;
}				t_material;

t_material		new_material(t_vector3 color);

#endif
