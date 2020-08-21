#include "../includes/rtv1.h"

static	void	load_kernel(t_rt *data)
{

}

t_rgba		*render(t_cl *cl, int w, int h)
{
	cl_mem		output_buffer;
	t_rgba		*res;

	if (!(res = (t_rgba*)malloc(sizeof(t_rgba) * w * h)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY,
								   sizeof(t_rgba) * w * h, NULL, NULL);

	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);

	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0,
						sizeof(t_rgba) * w * h,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
}
