#include "miniRT.h"

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit, double angle)
{
	double	m;

	m = dot_vec3(ray->dir, *obj->dir) * obj->height + dot_vec3(sub_vec3(ray->origin, *obj->origin), *obj->dir);
	hit->dir = sub_vec3(sub_vec3(hit->origin, *obj->origin), mul_vec3_and_const(*obj->dir, (1 + tan(angle) * tan(angle)) * m));
}

_Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];
	t_vec3	obj_to_origin;
	double	angle;

	radius = obj->diameter * 0.5;
	angle = 2 * asin(radius / sqrt(obj->height * obj->height + radius * radius));
	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
	coeff[A] = dot_vec3(ray->dir, ray->dir) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(ray->dir, *obj->dir);
	coeff[B] = 2 * dot_vec3(ray->dir, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
	coeff[C] = dot_vec3(obj_to_origin, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(obj_to_origin, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(
				ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit, angle);
		normalize_vec3(&hit->dir);
		check_direction_normal(ray, obj, hit);
		return (TRUE);
	}
	return (FALSE);
}
