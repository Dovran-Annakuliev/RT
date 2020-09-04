#include "../includes/rtv1.h"

static float	**new_res_array(int w, int h)
{
	float		**res;
	int			i;

	if (!(res = (float**)malloc(sizeof(float*) * w * h)))
		error(MALLOC_ERROR, "renderer malloc error");
	i = 0;
	while (i < h * w)
	{
		if (!(res[i] = (float*)malloc(sizeof(float) * 4)))
				error(MALLOC_ERROR, "renderer malloc error");
		i++;
	}
	return (res);
}

float		*render(t_cl *cl, int w, int h, t_obj o[3])
{
	cl_mem		output_buffer;
	cl_mem		obj_buffer;
	float		*res;
	cl_int		e;
	t_light		l;
	float 		fov;

	fov = 90.0f;

	l = new_light_source(new_vector3(100.0f, 100.0f, 100.0f), 0.7f);
	if (!(res = (float*)malloc(sizeof(float) * w * h * 4)))
		error(MALLOC_ERROR, "result buffer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(float) * w * h * 4, NULL, &e);
//	ft_printf("out_buff = %d\n", e);
	obj_buffer = clCreateBuffer(cl->context, CL_MEM_READ_ONLY, sizeof(t_obj) * 3, NULL, &e);
//	ft_printf("obj_buff = %d\n", e);;
	e = clEnqueueWriteBuffer(cl->queue, obj_buffer, CL_TRUE, 0, sizeof(t_obj) * 3, o, 0, NULL, NULL);
//	ft_printf("write_obj_buff = %d\n", e);
	e = clSetKernelArg(cl->kernel, 0, sizeof(float), &fov);
//	ft_printf("arg0 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &obj_buffer);
//	ft_printf("arg1 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 2, sizeof(t_light), &l);
//	ft_printf("arg2 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &output_buffer);
//	ft_printf("arg3 = %d\n", e);
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);
	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(float) * w * h * 4,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
