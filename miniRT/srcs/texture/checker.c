#include "miniRT.h"

void	get_checker_size(t_ray hit, double *checker_size)
{
	if (hit.obj->type == SPHERE || hit.obj->type == SKY)
	{
		checker_size[U] = 30;
		checker_size[V] = 15;
	}
	if (hit.obj->type == PLANE)
	{
		checker_size[U] = 0.5;
		checker_size[V] = 1;
	}
	if (hit.obj->type == CYLINDER)
	{
		checker_size[U] = 15;
		checker_size[V] = 1;
	}
	if (hit.obj->type == DISK || hit.obj->type == SQUARE)
	{
		checker_size[U] = 15;
		checker_size[V] = 15;
	}
}

void	create_checker(t_ray *hit)
{
	t_vec2	uv;
	int		floor_uv[2];
	double	checker_size[2];

	hit->obj->get_uv_coord(*hit, &uv);
	get_checker_size(*hit, checker_size);
	floor_uv[U] = floor(uv.coord[U] * checker_size[U]);
	floor_uv[V] = floor(uv.coord[V] * checker_size[V]);
	if ((floor_uv[U] + floor_uv[V]) % 2 == 0)
		return ;
	copy_vec3(&hit->color, *hit->obj->color_checker);
}

int	parse_checker(t_obj *obj, char *rgb)
{
	int	ret;

	obj->has_texture = CHECKER;
	ret = fill_rgb(rgb, obj->color_checker);
	return (ret);
}
