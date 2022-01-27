#include "miniRT.h"

_Bool	hit_plan(t_ray *ray, t_obj *obj, t_vec3 *intersection, t_vec3 *normal)
{
	double	denominator;
	t_vec3	tmp;
	double	hit_point;

	*normal = get_normalized_vec3(*obj->dir);
	denominator = dot_product_vec3(*normal, ray->dir);
	if (denominator < 1e-6)
		return (FALSE);
	tmp = sub_vec3(*obj->origin, ray->origin);
	hit_point = dot_product_vec3(tmp, *normal) / denominator;
	if (hit_point >= 0)
	{
		// printf("hit_point = %f\n", hit_point);
		*intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, hit_point));
		return (TRUE);
	}
	return (FALSE);
}
