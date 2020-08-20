#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;

	data = init_data();
	SDL_RenderCopy(data->renderer, data->texture, NULL, NULL);
	SDL_RenderPresent(data->renderer);
	SDL_Delay(5000);
	close_rt(data);

	return (0);
}
