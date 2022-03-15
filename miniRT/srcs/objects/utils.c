#include "miniRT.h"

void	check_direction_normal(t_ray *ray, t_obj *obj, t_ray *hit)
{
	if (dot_vec3(hit->dir, ray->dir) > 0.001)
	{
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		if (BONUS && obj->type == SPHERE)
			obj->inside_object = TRUE;
	}
}

t_vec3	get_hit_point(t_ray ray)
{
	t_vec3	hit_point;

	hit_point = add_vec3(ray.origin, mul_vec3_and_const(ray.dir, ray.dist));
	return (hit_point);
}
