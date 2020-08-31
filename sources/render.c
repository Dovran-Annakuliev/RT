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
	float		*res;
	t_sphere	s;
	t_light		l;
	float 		fov;

	fov = 90.0f;
	s = new_sphere(new_vector3(0.0f, 0.0f, -15.0f), 10.0f, new_material(new_vector3(240, 180, 50)));
	l = new_light_source(new_vector3(0.0f, -1000.0f, 20.0f), 1.0f);
	if (!(res = (float*)malloc(sizeof(float) * w * h * 4)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(float) * w * h * 4, NULL, NULL);
	clSetKernelArg(cl->kernel, 0, sizeof(float), &fov);
	clSetKernelArg(cl->kernel, 1, sizeof(t_sphere), &s);
	clSetKernelArg(cl->kernel, 2, sizeof(t_light), &l);
	clSetKernelArg(cl->kernel, 3, sizeof(cl_mem), &output_buffer);
	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
						   cl->global_size, NULL, 0, NULL, NULL);
	clFinish(cl->queue);
	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(float) * w * h * 4,
						res, 0, NULL, NULL);
	clFinish(cl->queue);
	clReleaseMemObject(output_buffer);
	return (res);
}
