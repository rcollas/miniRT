#include "miniRT.h"

_Bool	hit_hyperboloid(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];
	t_vec3	obj_to_origin;

	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
	radius = obj->diameter;
	coeff[A] = ray->dir.coord[Z] * ray->dir.coord[Z] - ray->dir.coord[X] * ray->dir.coord[X] - ray->dir.coord[Y] * ray->dir.coord[Y];
	coeff[B] = 2 * (obj_to_origin.coord[Z] * ray->dir.coord[Z] - obj_to_origin.coord[X] * ray->dir.coord[X] - obj_to_origin.coord[Y] * ray->dir.coord[Y]);
	coeff[C] = obj_to_origin.coord[Z] * obj_to_origin.coord[Z] + radius - obj_to_origin.coord[X] * obj_to_origin.coord[X] - obj_to_origin.coord[Y] * obj_to_origin.coord[Y];
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(
				ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		// hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		hit->dir = create_vec3(-2.0 * hit->origin.coord[X], -2.0 * hit->origin.coord[Y], hit->origin.coord[Z]);
		normalize_vec3(&hit->dir);
		check_direction_normal(ray, obj, hit);
		return (TRUE);
	}
	return (FALSE);
}
