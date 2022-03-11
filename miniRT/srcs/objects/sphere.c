#include "miniRT.h"

_Bool	hit_sphere(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];

	radius = obj->diameter * 0.5;
	coeff[A] = dot_vec3(ray->dir, ray->dir);
	coeff[B] = 2 * dot_vec3(ray->dir, sub_vec3(ray->origin, *obj->origin));
	coeff[C] = get_norm2_vec3(
			sub_vec3(ray->origin, *obj->origin)) - radius * radius;
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(
				ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		check_direction_normal(ray, obj, hit);
		return (TRUE);
	}
	return (FALSE);
}
