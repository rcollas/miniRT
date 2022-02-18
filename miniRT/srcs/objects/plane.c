#include "miniRT.h"

_Bool	hit_plane(t_ray *ray, t_obj *obj, t_hit *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->normal = get_normalized_vec3(*obj->dir);
	check_direction_normal(ray, hit);
	denominator = dot_vec3(hit->normal, ray->dir);
	tmp = sub_vec3(*obj->origin, ray->origin);
	hit->dist = dot_vec3(tmp, hit->normal) / denominator;
	if (hit->dist >= 1e-6)
	{
		ray->closest_hit = hit->dist;
		hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, hit->dist));
		return (TRUE);
	}
	return (FALSE);
}
