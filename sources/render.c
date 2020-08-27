#include "../includes/rtv1.h"

int		*render(t_cl *cl, int w, int h)
{
	cl_mem		output_buffer;
	int		*res;
	t_vector3	orig;
	t_vector3	dir;
	t_sphere	s;

	orig = new_vector3(0.0f, 0.0f, 0.0f); // mb 0,0,5  - somewhere on z-axis
	dir = new_vector3(0.0f, 0.0f, -1.0f);
	s = new_sphere(new_vector3(0.0f, 0.0f, -20.0f), 10);
	if (!(res = (int*)malloc(sizeof(int) * w * h)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(int) * w * h, NULL, NULL);
	clSetKernelArg(cl->kernel, 0, sizeof(t_vector3), &orig);
	clSetKernelArg(cl->kernel, 1, sizeof(t_vector3), &dir);
	clSetKernelArg(cl->kernel, 2, sizeof(t_sphere), &s);
	clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &output_buffer);
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);
	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(int) * w * h,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
