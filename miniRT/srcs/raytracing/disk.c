#include "miniRT.h"

_Bool	hit_disk(t_ray *ray, t_obj *obj, t_hit *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->normal = get_normalized_vec3(*obj->dir);
	denominator = dot_vec3(hit->normal, ray->dir);
	// if (denominator < 1e-6)
	// 	return (FALSE);
	tmp = sub_vec3(*obj->origin, ray->origin);
	// printf("x = %f | y = %f | z = %f\n", tmp.x, tmp.y, tmp.z);
	hit->dist = dot_vec3(tmp, hit->normal) / denominator;
	// printf("hit_point = %f\n", hit_point);
	if (hit->dist >= 0)
	{
		ray->closest_hit = hit->dist;
		hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, hit->dist));
		return (TRUE);
	}
	return (FALSE);
}
