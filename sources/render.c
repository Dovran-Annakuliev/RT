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

float		*render(t_rt *rt)
{
	cl_mem		output_buffer;
	cl_mem		obj_buffer;
	float		*res;
	cl_int		e;
	t_light		l;

	l = new_light_source((cl_float3){2.0f, 1.0f, 1.0f}, 0.7f);
	if (!(res = (float*)malloc(sizeof(float) * rt->width * rt->height * 4)))
		error(MALLOC_ERROR, "result buffer malloc error");
	output_buffer = clCreateBuffer(rt->cl.context, CL_MEM_WRITE_ONLY, sizeof(float) * rt->width * rt->height * 4, NULL, &e);
//	ft_printf("out_buff = %d\n", e);
	obj_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY, sizeof(t_obj) * 3, NULL, &e);
//	ft_printf("obj_buff = %d\n", e);;
	e = clEnqueueWriteBuffer(rt->cl.queue, obj_buffer, CL_TRUE, 0, sizeof(t_obj) * 3, rt->o, 0, NULL, NULL);
//	ft_printf("write_obj_buff = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 0, sizeof(t_camera), &rt->camera);
//	ft_printf("arg0 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 1, sizeof(cl_mem), &obj_buffer);
//	ft_printf("arg1 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 2, sizeof(t_light), &l);
//	ft_printf("arg2 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 3, sizeof(cl_mem), &output_buffer);
//	ft_printf("arg3 = %d\n", e);
	clEnqueueNDRangeKernel(rt->cl.queue, rt->cl.kernel, rt->cl.dim, NULL,
						   rt->cl.global_size, NULL, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clEnqueueReadBuffer(rt->cl.queue, output_buffer, CL_TRUE, 0, sizeof(float) * rt->width * rt->height * 4,
						res, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
