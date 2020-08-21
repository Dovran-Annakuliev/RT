#include "../includes/rtv1.h"

void 		update_texture(SDL_Texture *texture, int width, int height, int *r)
{
	Uint32				*pixels;
	int					pitch;
	SDL_PixelFormat		*format;

	if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) != 0)
		error(TEXTURE_LOCK_ERROR, SDL_GetError());
	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	ft_printf("color = %d\n", r[0]);
	for (int i = 0; i < height * width ; ++i)
	{
		pixels[i] = SDL_MapRGBA(format, r[i], 0, 0, 0);
	}
	SDL_UnlockTexture(texture);
}
