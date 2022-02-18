#include "miniRT.h"

_Bool	hit_plane(t_ray *ray, t_obj *obj, t_hit *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->normal = get_normalized_vec3(*obj->dir);
	normalize_vec3(&ray->dir);
	check_direction_normal(ray, hit);
	denominator = dot_vec3(hit->normal, ray->dir);
	if (fabs(denominator) > 1e-6)
	{
		printf("denominator = %f\n", denominator);
		tmp = sub_vec3(*obj->origin, ray->origin);
		hit->dist = dot_vec3(tmp, hit->normal);
		hit->dist /= denominator;
		if (hit->dist >= 0)
		{
			ray->closest_hit = hit->dist;
			hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, hit->dist));
			return (TRUE);
		}
	}
	return (FALSE);
}
