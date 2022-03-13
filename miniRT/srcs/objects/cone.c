#include "miniRT.h"

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit, double angle)
{
	double	m;

	m = dot_vec3(ray->dir, *obj->dir) * hit->dist;
	m += dot_vec3(sub_vec3(ray->origin, *obj->origin), *obj->dir);
	hit->dir = sub_vec3(sub_vec3(hit->origin, *obj->origin), mul_vec3_and_const(*obj->dir, (1 + tan(angle) * tan(angle)) * m));
	normalize_vec3(&hit->dir);
	check_direction_normal(ray, obj, hit);
}

_Bool	solve_quadratic_cone(
	double *coeff, double *roots, double *closest_hit)
{
	double	delta;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[0] < 0 && roots[1] < 0)
		return (FALSE);
	if (roots[0] > roots[1])
		*closest_hit = roots[0];
	else
		*closest_hit = roots[1];
	return (TRUE);
}

t_vec3	transform_point_in_obj_space_vec3(
	t_vec3 hit_point, t_vec3 obj_origin, double max_dimension)
{
	t_vec3	new_point;

	(void)max_dimension;
	new_point.coord[X] = hit_point.coord[X] - obj_origin.coord[X];
	// new_point.coord[X] /= max_dimension;
	new_point.coord[Y] = hit_point.coord[Y] - obj_origin.coord[Y];
	// new_point.coord[Y] /= max_dimension;
	new_point.coord[Z] = hit_point.coord[Z] - obj_origin.coord[Z];
	// new_point.coord[Z] /= max_dimension;
	return (new_point);
}

// _Bool	check_height(t_obj *obj, t_ray hit)
// {
// 	t_vec3	object;
// 	t_vec3	point;
// 	double	radius;
// 	double	max_dimension;

// 	radius = obj->diameter * 0.5;
// 	max_dimension = sqrt(obj->height * obj->height + radius * radius);
// 	point = transform_point_in_obj_space_vec3(hit.origin, *obj->origin, obj->height);
// 	object = *obj->origin;
// 	if (point.coord[Y] > object.coord[Y]
// 		|| point.coord[Y] < object.coord[Y] - obj->height)
// 		return (FALSE);
// 	return (TRUE);
// }

_Bool	check_height(t_ray *ray, t_obj *obj)
{
	t_vec3	vec_1;
	t_vec3	vec_2;
	double	dot_1;
	double	dot_2;

	vec_1 = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
	vec_2 = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height));
	dot_1 = dot_vec3(*obj->dir, sub_vec3(vec_1, *obj->origin));
	dot_2 = dot_vec3(*obj->dir, sub_vec3(vec_1, vec_2));
	if (dot_1 < 0.0 || dot_2 > 0.0)
		return (FALSE);
	return (TRUE);
}

_Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];
	t_vec3	obj_to_origin;
	double	angle;

	normalize_vec3(obj->dir);
	radius = obj->diameter * 0.5;
	angle = 2 * asin(radius / sqrt(obj->height * obj->height + radius * radius));
	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
	coeff[A] = dot_vec3(ray->dir, ray->dir) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(ray->dir, *obj->dir);
	coeff[B] = 2 * dot_vec3(ray->dir, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
	coeff[C] = dot_vec3(obj_to_origin, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(obj_to_origin, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
	if (solve_quadratic_equation(coeff, roots, &ray->dist)) // || hit_disk(ray, obj, hit))
	{
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		if (!check_height(ray, obj))
			return (FALSE);
		compute_normal_cone(ray, obj, hit, angle);
		return (TRUE);
	}
	return (FALSE);
}
