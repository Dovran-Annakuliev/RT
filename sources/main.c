#include "../includes/rtv1.h"

int main(int argc, char **argv)
{
	t_rt *data;

	data = init_data();
	close_rt(data);

	return (0);
}
