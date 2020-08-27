#include "../includes/rtv1.h"

/*
 ** ---------------------------------------------
 ** ray eqation O + tD (1)
 ** ---------------------------------------------
 ** x^2 + y^2 + z^2 = R^2 2)
 ** ---------------------------------------------
 ** may P be the point (origin?) of x,y,z, then:
 ** P^2 - R^2 = 0 (3)
 ** ---------------------------------------------
 ** substitute (1) in (2):
 ** |O + tD|^2 - R^2 = 0
 ** ---------------------------------------------
 ** O^2 + D^2*t^2 + 2ODt - R^2 = 0 (quadratic equation f(x) = ax^2 + bx + c
 ** where: a = D^2, b = 2OD, c = O^2 - R^2
 ** ---------------------------------------------
 ** If sphere is not located in the origin, then we rewrite (3):
 ** (P - C)^2 - R^2 = 0
 ** |O + tD - C|^2 - R^2 = 0
 ** which give us: a = 1, b = 2D(O - C), c = (O - C)^2 - R^2
 */


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
