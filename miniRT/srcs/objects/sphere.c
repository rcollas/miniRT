#include "miniRT.h"

void	check_direction_normal(t_ray *ray, t_hit *hit)
{
	if (dot_vec3(hit->normal, ray->dir) > 0)
		hit->normal = mul_vec3_and_const(hit->normal, -1);
}

_Bool	hit_sphere(t_ray *ray, t_obj *obj, t_hit *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];

	radius = obj->diameter * 0.5;
	coeff[A] = dot_vec3(ray->dir, ray->dir);
	coeff[B] = 2 * dot_vec3(ray->dir, sub_vec3(ray->origin, *obj->origin));
	coeff[C] = get_norm2_vec3(sub_vec3(ray->origin, *obj->origin)) - radius * radius;
	if (solve_quadratic_equation(coeff, roots, &ray->closest_hit))
	{
		hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
		hit->dist = ray->closest_hit;
		hit->normal = get_normalized_vec3(sub_vec3(hit->intersection, *obj->origin));
		check_direction_normal(ray, hit);
		return (TRUE);
	}
	return (FALSE);
}
