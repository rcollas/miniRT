#include "miniRT.h"

void	check_dir_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	dot_hit_ray;
	double	dot_obj_ray;

	normalize_vec3(&ray->dir);
	dot_hit_ray = dot_vec3(hit->dir, ray->dir);
	dot_obj_ray = dot_vec3(*obj->dir, ray->dir);
	if (dot_hit_ray > 0.00001)
	{
		if (dot_hit_ray < 0.2 && dot_obj_ray > 0.0001)
			return ;
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		hit->inside_object = TRUE;
	}
}

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	length;
	t_vec3	tmp;

	(void)ray;
	length = get_norm_vec3(sub_vec3(hit->origin, *obj->origin));
	tmp = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, length));
	hit->dir = sub_vec3(hit->origin, tmp);
	normalize_vec3(&hit->dir);
	check_dir_normal_cone(ray, obj, hit);
	normalize_vec3(&hit->dir);
}

_Bool	check_cone_height(t_ray *ray, t_obj *obj, double ray_dist)
{
	t_vec3	point_on_ray;
	t_vec3	base_cone;
	double	dot_origin;
	double	dot_height;

	point_on_ray = mul_vec3_and_const(ray->dir, ray_dist);
	point_on_ray = add_vec3(ray->origin, point_on_ray);
	base_cone = mul_vec3_and_const(*obj->dir, obj->height);
	base_cone = add_vec3(*obj->origin, base_cone);
	dot_origin = dot_vec3(*obj->dir, sub_vec3(point_on_ray, *obj->origin));
	dot_height = dot_vec3(*obj->dir, sub_vec3(point_on_ray, base_cone));
	if (dot_origin < 0.001 || dot_height > 0.001)
		return (FALSE);
	return (TRUE);
}
