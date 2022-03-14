#include "miniRT.h"

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit, double angle)
{
	double	m;
	double	radius;

	radius = obj->diameter / 2.0;
	m = dot_vec3(ray->dir, *obj->dir) * hit->dist;
	m += dot_vec3(sub_vec3(ray->origin, *obj->origin), *obj->dir);
	hit->dir = sub_vec3(sub_vec3(hit->origin, *obj->origin), mul_vec3_and_const(*obj->dir, (1 + tan(angle) * tan(angle)) * m));
	// hit->dir.coord[X] = (hit->origin.coord[X] - obj->origin->coord[X]) * (obj->height / radius);
	// hit->dir.coord[X] = radius / obj->height;
	// hit->dir.coord[Z] = (hit->origin.coord[Z] - obj->origin->coord[Z]) * (obj->height / radius);
	normalize_vec3(&hit->dir);
	check_direction_normal(ray, obj, hit);
}

_Bool	solve_quadratic_cone(
	double *coeff, double *roots, double *closest_hit)
{
	double	delta;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (FALSE);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[0] >= 0)
		*closest_hit = roots[0];
	else if (roots[1] >= 0)
		*closest_hit = roots[1];
	else
		return (FALSE);
	return (TRUE);
}

_Bool	check_height(t_ray *ray, t_obj *obj)
{
	t_vec3	vec_1;
	t_vec3	vec_2;
	double	dot_origin;
	double	dot_height;

	// printf("cam_dir : %f  %f  %f\n", cam_dir.coord[X], cam_dir.coord[Y], cam_dir.coord[Z]);
	vec_1 = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
	vec_2 = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height));
	dot_origin = dot_vec3(*obj->dir, sub_vec3(vec_1, *obj->origin));
	dot_height = dot_vec3(*obj->dir, sub_vec3(vec_1, vec_2));
	if (dot_origin < 0.0 || dot_height > 0.0)
		return (FALSE);
	return (TRUE);
}

// _Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
// {
// 	double	coeff[3];
// 	double	radius;
// 	double	roots[2];
// 	t_vec3	obj_to_origin;
// 	double	angle;

// 	radius = obj->diameter * 0.5;
// 	angle = 2 * asin(radius / sqrt(obj->height * obj->height + radius * radius));
// 	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
// 	coeff[A] = dot_vec3(ray->dir, ray->dir) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(ray->dir, *obj->dir);
// 	coeff[B] = 2 * dot_vec3(ray->dir, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(ray->dir, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
// 	coeff[C] = dot_vec3(obj_to_origin, obj_to_origin) - (1.0 + tan(angle) * tan(angle)) * dot_vec3(obj_to_origin, *obj->dir) * dot_vec3(obj_to_origin, *obj->dir);
// 	if (solve_quadratic_cone(coeff, roots, &ray->dist)) // || hit_disk(ray, obj, hit))
// 	{
// 		if (!check_height(ray, obj))
// 			return (FALSE);
// 		hit->origin = get_hit_point(*ray);
// 		hit->dist = ray->dist;
// 		compute_normal_cone(ray, obj, hit, angle);
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

_Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	double	roots[2];
	t_vec3	obj_to_origin;
	double	angle;
	t_vec3	theta;
	double	s_d1;
	double	s_d2;

	theta = get_normalized_vec3(*obj->dir);
	radius = obj->diameter * 0.5;
	angle = (radius * radius) / (obj->height * obj->height);
	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
	s_d1 = dot_vec3(ray->dir, theta);
	s_d2 = dot_vec3(obj_to_origin, theta);
	coeff[A] = dot_vec3(ray->dir, ray->dir) - angle * s_d1 * s_d1 - s_d1 * s_d1;
	coeff[B] = 2 * (dot_vec3(ray->dir, obj_to_origin) - angle * s_d1 * s_d2 - s_d1 * s_d2);
	coeff[C] = dot_vec3(obj_to_origin, obj_to_origin) - angle * s_d2 * s_d2 - s_d2 * s_d2;
	if (solve_quadratic_equation(coeff, roots, &ray->dist)) // || hit_disk(ray, obj, hit))
	{
		if (!check_height(ray, obj))
			return (FALSE);
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit, angle);
		return (TRUE);
	}
	return (FALSE);
}
