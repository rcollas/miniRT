#include "miniRT.h"

void	get_coeff(float coeff[3], t_ray *ray, t_obj *obj)
{
	t_vec3	normalized_dir;
	t_vec3	cyl_to_origin;
	t_vec3	new_ray_dir;
	float	radius;

	radius = obj->diameter / 2;
	normalized_dir = get_normalized_vec3(*obj->dir);
	cyl_to_origin = sub_vec3(ray->origin, *obj->origin);
	new_ray_dir = cross_vec3(ray->dir, normalized_dir);
	coeff[A] = dot_vec3(new_ray_dir, new_ray_dir);
	coeff[B] = 2 * dot_vec3(
			new_ray_dir, cross_vec3(cyl_to_origin, normalized_dir));
	coeff[C] = dot_vec3(cross_vec3(cyl_to_origin, normalized_dir),
			cross_vec3(cyl_to_origin, normalized_dir));
	coeff[C] -= (radius * radius);
}

_Bool	hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit)
{
	float	coeff[3];
	float	roots[2];

	get_coeff(coeff, ray, obj);
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(
				ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		check_direction_normal(ray, hit);
		if (get_norm_vec3(sub_vec3(hit->origin, *obj->origin)) > obj->height)
		{
			ray->dist = roots[1];
			hit->dist = ray->dist;
			hit->origin = add_vec3(
					ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		}
		if (get_norm_vec3(sub_vec3(hit->origin, *obj->origin)) > obj->height)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
