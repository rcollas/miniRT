#include "miniRT.h"

_Bool	hit_plane(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->dir = get_normalized_vec3(*obj->dir);
	normalize_vec3(&ray->dir);
	check_direction_normal(ray, obj, hit);
	denominator = dot_vec3(hit->dir, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		tmp = sub_vec3(*obj->origin, ray->origin);
		hit->dist = dot_vec3(tmp, hit->dir);
		hit->dist /= denominator;
		if (hit->dist > 0)
		{
			ray->dist = hit->dist;
			hit->origin = get_hit_point(*ray);
			return (TRUE);
		}
	}
	return (FALSE);
}
