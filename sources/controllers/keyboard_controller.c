#include "../../includes/rtv1.h"

void 		keyboard_controller(SDL_Event *e)
{
	ft_printf("key_number = %d\n", e->key.keysym.sym);
}
