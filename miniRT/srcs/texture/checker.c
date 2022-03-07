#include "miniRT.h"

void	get_checker_size(t_ray hit, double *checker_size)
{
	if (hit.type == SPHERE)
	{
		checker_size[U] = 30;
		checker_size[V] = 15;
	}
	if (hit.type == PLANE || hit.type == DISK)
	{
		checker_size[U] = 0.5;
		checker_size[V] = 1;
	}
	if (hit.type == CYLINDER)
	{
		checker_size[U] = 15;
		checker_size[V] = 1;
	}
}

void	create_checker(t_ray *hit)
{
	double	coord_uv[2];
	int		floor_uv[2];
	double	checker_size[2];

	hit->obj->get_uv_coord(*hit, coord_uv);
	get_checker_size(*hit, checker_size);
	floor_uv[U] = floor(coord_uv[U] * checker_size[U]);
	floor_uv[V] = floor(coord_uv[V] * checker_size[V]);
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
