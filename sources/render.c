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
	t_obj		s;
	t_obj		p;
	t_light		l;
	float 		fov;

	fov = 90.0f;
//	s = new_sphere((cl_float3)(0.0, 0.0, -15.0), 10.0, new_material(new_vector3(240, 180, 50)));
//	p = new_plane(new_vector3(0.0f, 0.0f, 0.0f), new_vector3(0.0f, -1.0f, 0.0f));
	s = new_sphere((cl_float3){0.0f, 0.0f, -15.0f}, 10.0, new_material(new_vector3(240, 180, 50)));
	p = new_plane((cl_float3){0.0, 0.0, 0.0}, (cl_float3){0.0, -1.0, 0.0}, new_material(new_vector3(0, 255, 0)));

//
//	objects = new_obj_list(&s, s.type);
//	push_back(objects, &p, p.type);
//	push_back(objects, &s, s.type);
//	push_back(objects, &s, s.type);
//	push_back(objects, &p, p.type);
//	push_back(objects, &s, s.type);
////	del
//	t_obj	*tmp;
//	tmp = objects;
//	int i = 0;
//	while (tmp != NULL)
//	{
//		if (tmp->type == 0)
//		{
//			t_sphere *ss = (t_sphere *)tmp->content;
//			ft_printf("%d type = %d\n", i, ss->type);
//		}
//		if (tmp->type == 1)
//		{
//			t_plane *ss = (t_plane *)tmp->content;
//			ft_printf("%d type = %d\n", i, ss->type);
//		}
//		tmp = tmp->next;
//		i++;
//	}

	l = new_light_source(new_vector3(100.0f, -1000.0f, 100.0f), 1.0f);
	if (!(res = (float*)malloc(sizeof(float) * w * h * 4)))
		error(MALLOC_ERROR, "renderer malloc error");
	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(float) * w * h * 4, NULL, NULL);
	clSetKernelArg(cl->kernel, 0, sizeof(float), &fov);
	clSetKernelArg(cl->kernel, 1, sizeof(t_obj), &s);
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
