#include "miniRT.h"

_Bool	solve_quadratic(double *coeff, double *roots, double *closest_hit)
{
	double	delta;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[1] < 0)
		return (FALSE);
	if (roots[0] > 0)
		*closest_hit = roots[0];
	else
		*closest_hit = roots[1];
	return (TRUE);
}

_Bool	hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	radius;
	double	coeff[3];
	double	roots[2];
	t_vec3	normalized_dir;
	t_vec3	cylinder_to_origin;
	t_vec3	new_ray_dir;

	radius = obj->diameter / 2;
	normalized_dir = get_normalized_vec3(*obj->dir);
	cylinder_to_origin = sub_vec3(ray->origin, *obj->origin);
	new_ray_dir = cross_vec3(ray->dir, normalized_dir);
	coeff[A] = dot_vec3(new_ray_dir, new_ray_dir);
	coeff[B] = 2 * dot_vec3(new_ray_dir, cross_vec3(cylinder_to_origin, normalized_dir));
	coeff[C] = dot_vec3(cross_vec3(cylinder_to_origin, normalized_dir), cross_vec3(cylinder_to_origin, normalized_dir)) - radius * radius;
	if (solve_quadratic(coeff, roots, &ray->closest_hit))
	{
		hit->origin = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
		hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		if (get_norm_vec3(sub_vec3(hit->origin, *obj->origin)) > obj->height)
		{
			ray->closest_hit = roots[1];
			hit->origin = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
		}
		if (get_norm_vec3(sub_vec3(hit->origin, *obj->origin)) > obj->height)
		{
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}
