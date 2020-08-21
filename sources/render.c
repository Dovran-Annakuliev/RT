#include "../includes/rtv1.h"

static	void	load_kernel(t_cl *cl, t_vector3 orig, t_vector3 dir, cl_mem *ob)
{
	clSetKernelArg(cl->kernel, 0, sizeof(t_vector3), &orig);
	clSetKernelArg(cl->kernel, 1, sizeof(t_vector3), &dir);
	clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), ob);
}

int		*render(t_cl *cl, int w, int h)
{
	cl_mem		output_buffer;
	int		*res;
	t_vector3	orig;
	t_vector3	dir;

	orig = new_vector3(0.0f, 0.0f, 0.0f);
	dir = new_vector3(1.0f, 1.0f, 1.0f);
	if (!(res = (int*)malloc(sizeof(int) * w * h)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
								   sizeof(int) * w * h, NULL, NULL);
//	load_kernel(cl, orig, dir, &output_buffer);
	clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &output_buffer);
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);
	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(int) * w * h,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
