#include "miniRT.h"


_Bool	hit_cylinder(t_ray *ray, t_obj *obj, t_hit *hit)
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
	if (solve_quadratic_equation(coeff, roots, &ray->closest_hit))
	{
		hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
		hit->dist = ray->closest_hit;
		hit->normal = get_normalized_vec3(sub_vec3(hit->intersection, *obj->origin));
		check_direction_normal(ray, hit);
		if (get_norm_vec3(sub_vec3(hit->intersection, *obj->origin)) > obj->height)
		{
			ray->closest_hit = roots[1];
			hit->intersection = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
		}
		if (get_norm_vec3(sub_vec3(hit->intersection, *obj->origin)) > obj->height)
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}
