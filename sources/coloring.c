#include "../includes/rtv1.h"

void		update_texture(SDL_Texture *texture,
							int width, int height, float *r)
{
	Uint32				*pixels;
	int					pitch;
	SDL_PixelFormat		*format;
	int					i;
	int					j;

	if (SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) != 0)
		error(TEXTURE_LOCK_ERROR, SDL_GetError());
	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	i = 0;
	j = 0;
	while (i < width * height)
	{
		pixels[i] = SDL_MapRGBA(format, r[j++], r[j++], r[j++], r[j++]);
		i++;
	}
	SDL_UnlockTexture(texture);
}
