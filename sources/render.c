#include "../includes/rtv1.h"

void		render(t_rt *rt)
{
	cl_mem		output_buffer;
	cl_mem		obj_buffer;
	cl_mem		light_buffer;
	cl_mem		rand_buffer;
	cl_int		e;

	printf("rendering\n");
	output_buffer = clCreateBuffer(rt->cl.context, CL_MEM_WRITE_ONLY, sizeof(float) * rt->width * rt->height * 4, NULL, &e);
//	ft_printf("out_buff = %d\n", e);

	obj_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY, sizeof(t_obj) * rt->parse.obj_size, NULL, &e);
//	ft_printf("obj_buff = %d\n", e);

	light_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY, sizeof(t_light) * rt->parse.light_size, NULL, &e);
//	ft_printf("light_buff = %d\n", e);

	rand_buffer = clCreateBuffer(rt->cl.context, CL_MEM_READ_ONLY, sizeof(float) * rt->width * rt->height * rt->samples, NULL, &e);
//	ft_printf("rand_buff = %d\n", e);;

	e = clEnqueueWriteBuffer(rt->cl.queue, obj_buffer, CL_TRUE, 0, sizeof(t_obj) * rt->parse.obj_size, rt->parse.obj, 0, NULL, NULL);
//	ft_printf("write_obj_buff = %d\n", e);

	e = clEnqueueWriteBuffer(rt->cl.queue, light_buffer, CL_TRUE, 0, sizeof(t_light) * rt->parse.light_size, rt->parse.light, 0, NULL, NULL);
//	ft_printf("write_obj_buff = %d\n", e);

	e = clEnqueueWriteBuffer(rt->cl.queue, rand_buffer, CL_TRUE, 0, sizeof(float) * rt->width * rt->height * rt->samples, rt->randoms, 0, NULL, NULL);
//	ft_printf("write_rend_buff = %d\n", e);
//	ft_printf("curr_camera = %d\n", rt->current_camera);
//	ft_printf("camera_size = %d\n", rt->parse.camera_size);
//	print_camera_info(rt->parse.camera[rt->current_camera], rt->current_camera);
	e = clSetKernelArg(rt->cl.kernel, 0, sizeof(t_camera), &rt->parse.camera[rt->current_camera]);
//	ft_printf("arg0 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 1, sizeof(cl_mem), &obj_buffer);
//	ft_printf("arg1 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 2, sizeof(cl_mem), &rand_buffer);
//	ft_printf("arg2 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 3, sizeof(int), &rt->samples);
//	ft_printf("arg3 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 4, sizeof(cl_mem), &light_buffer);
//	ft_printf("arg4 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 5, sizeof(cl_mem), &output_buffer);
//	ft_printf("arg5 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 6, sizeof(int), &rt->parse.obj_size);
//	ft_printf("arg6 = %d\n", e);
	e = clSetKernelArg(rt->cl.kernel, 7, sizeof(int), &rt->parse.light_size);
//	ft_printf("arg7 = %d\n", e);
	clEnqueueNDRangeKernel(rt->cl.queue, rt->cl.kernel, rt->cl.dim, NULL,
						   rt->cl.global_size, NULL, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clEnqueueReadBuffer(rt->cl.queue, output_buffer, CL_TRUE, 0, sizeof(float) * rt->width * rt->height * 4,
						rt->res, 0, NULL, NULL);
	clFinish(rt->cl.queue);
	clReleaseMemObject(output_buffer);
	clReleaseMemObject(obj_buffer);
	clReleaseMemObject(rand_buffer);
	rt->update_status = 0;
}
