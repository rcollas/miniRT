#include "miniRT.h"

_Bool	hit_plan(t_ray *ray, t_obj *obj, t_hit *hit)
{
	double	denominator;
	t_vec3	tmp;

	hit->normal = get_normalized_vec3(*obj->dir);
	denominator = dot_vec3(hit->normal, ray->dir);
	// printf("denominator = %f\n", denominator);
	// if (denominator < 1e-6)
	// 	return (FALSE);
//	printf("obj_origin.x = %f | obj_origin.y = %f | obj_origin.z = %f\n", obj->origin->x, obj->origin->y, obj->origin->z);
	// printf("ray_origin.x = %f | ray_origin.y = %f | ray_origin.z = %f\n", ray->origin.x, ray->origin.y, ray->origin.z);
	tmp = sub_vec3(*obj->origin, ray->origin);
//	printf("x = %f | y = %f | z = %f\n", tmp.x, tmp.y, tmp.z);
	hit->dist = dot_vec3(tmp, hit->normal) / denominator;
	// printf("hit_point = %f\n", hit_point);
	if (hit->dist >= 0)
	{
		ray->closest_hit = hit->dist;
		hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, hit->dist));
		// printf("x = %f | y = %f | z = %f\n", hit->intersection.x, hit->intersection.y, hit->intersection.z);
		return (TRUE);
	}
	return (FALSE);
}
