#include "../includes/rtv1.h"

void 		update_texture(t_rt *data)
{
	if (SDL_LockTexture(data->texture, NULL, (void**)&data->pixels, &data->pitch) != 0)
		error(TEXTURE_LOCK_ERROR, SDL_GetError());
	SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	for (int i = 0; i < (data->pitch / 4) * data->height ; ++i)
	{
		data->pixels[i] = SDL_MapRGBA(format, 255, 0, 0, 255);
	}
	SDL_UnlockTexture(data->texture);
}
