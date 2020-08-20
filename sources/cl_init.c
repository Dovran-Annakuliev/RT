#include "../includes/rtv1.h"

static	int		get_lines(int fd)
{
	int		count;
	char	*line;

	count = 0;
	line = NULL;
	while (get_next_line(fd, &line))
	{
		count++;
		free(line);
	}
	return (count);
}

char			**get_kernel_source(t_cl *cl, char *type)
{
	int		i;
	int		fd;
	char	**source;
	char	*line;

	line = NULL;
	if (((fd = open(type, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(0);
	cl->count = get_lines(fd);
	close(fd);
	if (!(source = (char **)malloc(sizeof(char *) * cl->count)))
		error(MALLOC_ERROR);
	fd = open(type, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(source[i] = ft_strdup(line)))
			error(MALLOC_ERROR);
		free(line);
		line = NULL;
		i++;
	}
	close(fd);
	return (source);
}

void			cl_init(t_cl *cl, int width, int height)
{
	cl_int				ret;

	ret = clGetPlatformIDs(1, &cl->platform_id, NULL);
	ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
			&cl->device_id, NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &ret);
	cl->program = clCreateProgramWithSource(cl->context, cl->count,
			(const char **)cl->kernel_source, NULL, &ret);
	ret = clBuildProgram(cl->program, 1, &cl->device_id, NULL, NULL, NULL);
	cl->kernel = clCreateKernel(cl->program, "array_add", &ret);
	cl->queue = clCreateCommandQueue(cl->context, cl->device_id, 0, &ret);
	cl->dim = 2;
	cl->global_size[0] = width;
	cl->global_size[1] = height;
}

void			cl_free(t_cl *cl)
{
	int i;

	i = -1;
	clReleaseKernel(cl->kernel);
	clReleaseProgram(cl->program);
	clReleaseCommandQueue(cl->queue);
	clReleaseContext(cl->context);
	while (++i < cl->count)
		free(cl->kernel_source[i]);
	free(cl->kernel_source);
}
