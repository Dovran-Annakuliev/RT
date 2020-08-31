#ifndef LIGHTS_H
#define LIGHTS_H

#include "vectors.h"

typedef struct		s_light
{
	t_vector3		pos;
	float			intensity;
}					t_light;

t_light			new_light_source(t_vector3 pos, float intensity);

#endif
