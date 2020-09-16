#include "../includes/rtv1.h"

static	t_buffers	create_buffers(t_rt *rt)
{
	cl_int		e;
	t_buffers	buffers;

	buffers.output_buffer = clCreateBuffer(rt->cl.context, CL_MEM_WRITE_ONLY,
						sizeof(float) * rt->w * rt->h * 4, NULL, &e);
	ft_printf("out_buff = %d\n", e);
	buffers.obj_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY,
						sizeof(t_obj) * rt->parse.obj_size, NULL, &e);
	ft_printf("obj_buff = %d\n", e);
	buffers.light_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY,
						sizeof(t_light) * rt->parse.light_size, NULL, &e);
	ft_printf("light_buff = %d\n", e);
	buffers.rand_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY,
						sizeof(float) * rt->w * rt->h * rt->samples, NULL, &e);
	ft_printf("rand_buff = %d\n", e);
	e = clEnqueueWriteBuffer(rt->cl.queue, buffers.obj_buffer, CL_TRUE, 0,
		sizeof(t_obj) * rt->parse.obj_size, rt->parse.obj, 0, NULL, NULL);
	ft_printf("write_obj_buff = %d\n", e);
	e = clEnqueueWriteBuffer(rt->cl.queue, buffers.light_buffer, CL_TRUE, 0,
		sizeof(t_light) * rt->parse.light_size, rt->parse.light, 0, NULL, NULL);
	ft_printf("write_obj_buff = %d\n", e);
	e = clEnqueueWriteBuffer(rt->cl.queue, buffers.rand_buffer, CL_TRUE, 0,
	sizeof(float) * rt->w * rt->h * rt->samples, rt->randoms, 0, NULL, NULL);
	ft_printf("write_rand_buff = %d\n", e);
	return (buffers);
}

static	void		load_kernels(t_rt *rt, t_buffers b)
{
	cl_int		e;

	e = clSetKernelArg(rt->cl.kernel, 0, sizeof(t_camera),
					&rt->parse.camera[rt->current_camera]);
	ft_printf("arg0 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 1, sizeof(cl_mem), &b.obj_buffer);
	ft_printf("arg1 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 2, sizeof(cl_mem), &b.rand_buffer);
	ft_printf("arg2 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 3, sizeof(int), &rt->samples);
	ft_printf("arg3 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 4, sizeof(cl_mem), &b.light_buffer);
	ft_printf("arg4 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 5, sizeof(cl_mem), &b.output_buffer);
	ft_printf("arg5 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 6, sizeof(int), &rt->parse.obj_size);
	ft_printf("arg6 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 7, sizeof(int), &rt->parse.light_size);
	ft_printf("arg7 = %d\n", e);
}

void				render(t_rt *rt)
{
	t_buffers	buffers;

	buffers = create_buffers(rt);
	load_kernels(rt, buffers);
	clEnqueueNDRangeKernel(rt->cl.queue, rt->cl.kernel, rt->cl.dim, NULL,
							rt->cl.global_size, NULL, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clEnqueueReadBuffer(rt->cl.queue, buffers.output_buffer, CL_TRUE,
			0, sizeof(float) * rt->w * rt->h * 4, rt->res, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clReleaseMemObject(buffers.output_buffer);
	clReleaseMemObject(buffers.obj_buffer);
	clReleaseMemObject(buffers.rand_buffer);
	printf("rendering\n");
	rt->update_status = 0;
}
