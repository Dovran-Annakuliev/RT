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

float		*render(t_cl *cl, int w, int h)
{
	cl_mem		output_buffer;
	cl_mem		obj_buffer;
	float		*res;
	t_obj		o[3];
	cl_int		e;
	t_light		l;
	float 		fov;

	fov = 90.0f;
	o[0] = new_sphere((cl_float3){10.0f, 0.0f, -15.0f}, 2.0f, new_material((cl_float4){255, 0, 0, 0}));
	o[1] = new_sphere((cl_float3){0.0f, 0.0f, -10.0f}, 1.0f, new_material((cl_float4){0, 255, 0, 0}));
	o[2] = new_sphere((cl_float3){-20.0f, 0.0f, -15.0f}, 4.0f, new_material((cl_float4){0, 0, 255, 0}));


	l = new_light_source(new_vector3(100.0f, 100.0f, 100.0f), 0.7f);
	if (!(res = (float*)malloc(sizeof(float) * w * h * 4)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(float) * w * h * 4, NULL, &e);
	ft_printf("out_buff = %d\n", e);
	obj_buffer = clCreateBuffer(cl->context, CL_MEM_READ_ONLY, sizeof(o), NULL, &e);
	ft_printf("obj_buff = %d\n", e);
	e = clEnqueueWriteBuffer(cl->queue, obj_buffer, CL_TRUE, 0, sizeof(o), o, 0, NULL, NULL);
	ft_printf("write_obj_buff = %d\n", e);
	e = clSetKernelArg(cl->kernel, 0, sizeof(float), &fov);
	ft_printf("arg0 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &obj_buffer);
	ft_printf("arg1 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 2, sizeof(t_light), &l);
	ft_printf("arg2 = %d\n", e);
	e = clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &output_buffer);
	ft_printf("arg3 = %d\n", e);
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);
	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(float) * w * h * 4,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
