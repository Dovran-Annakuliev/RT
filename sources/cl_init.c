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

char			**get_kernel_source(t_cl *cl, char *path)
{
	int		i;
	int		fd;
	char	**source;
	char	*line;

	line = NULL;
	if (((fd = open(path, O_RDONLY)) < 0) || ((read(fd, line, 0)) < 0))
		error(0, "");

	cl->count = get_lines(fd);
	close(fd);
	if (!(source = (char **)malloc(sizeof(char *) * cl->count)))
		error(MALLOC_ERROR, "Malloc error");
	fd = open(path, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(source[i] = ft_strdup(line)))
			error(MALLOC_ERROR, "Malloc error");
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
	size_t log_size;

	ret = clGetPlatformIDs(1, &cl->platform_id, NULL);
	ret = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
			&cl->device_id, NULL);
	cl->context = clCreateContext(NULL, 1, &cl->device_id, NULL, NULL, &ret);
	cl->program = clCreateProgramWithSource(cl->context, cl->count,
			(const char **)cl->kernel_source, NULL, &ret);
	ft_printf("prog = %d\n", ret);
	ret = clBuildProgram(cl->program, 1, &cl->device_id, "-w -I kernels/", NULL, NULL);
	ft_printf("build = %d\n", ret);
	if (ret < 0)
	{
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
		char *log = (char *) malloc(sizeof(char) * log_size);
		log[log_size] = '\0';
		clGetProgramBuildInfo(cl->program, cl->device_id, CL_PROGRAM_BUILD_LOG, log_size + 1, log, NULL);
		ft_printf("%s\n", log);
		free(log);
	}
	cl->kernel = clCreateKernel(cl->program, "raytrace", &ret);
	ft_printf("kernel = %d\n", ret);
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
