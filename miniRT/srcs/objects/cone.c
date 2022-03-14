#include "miniRT.h"

void	check_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	(void)obj;
	(void)hit;
	(void)ray;
	if (dot_vec3(hit->dir, ray->dir) > 0)
	{
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		// if (BONUS && obj->type == SPHERE)
			// obj->inside_object = FALSE;
	}
}

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	length;

	(void)ray;
	length = get_norm_vec3(sub_vec3(hit->origin, *obj->origin));
	hit->dir = sub_vec3(hit->origin, add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, length)));
	normalize_vec3(&hit->dir);
	// check_normal_cone(ray, obj, hit);
}

_Bool	check_height(t_ray *ray, t_obj *obj)
{
	t_vec3	vec_1;
	t_vec3	vec_2;
	double	dot_origin;
	double	dot_height;

	vec_1 = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
	vec_2 = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height));
	dot_origin = dot_vec3(*obj->dir, sub_vec3(vec_1, *obj->origin));
	dot_height = dot_vec3(*obj->dir, sub_vec3(vec_1, vec_2));
	// if (dot_origin < 0.01 || dot_height > 0.01)
	if (dot_origin < 0 || dot_height > 0)
		return (FALSE);
	return (TRUE);
}

_Bool	hit_cone_caps(t_ray *ray, t_obj *obj, t_ray *hit)
{
	t_obj	cone_caps;

	cone_caps = *obj;
	cone_caps.origin->coord[X] = obj->origin->coord[X] + obj->dir->coord[X] * obj->height;
	cone_caps.origin->coord[Y] = obj->origin->coord[Y] + obj->dir->coord[Y] * obj->height;
	cone_caps.origin->coord[Z] = obj->origin->coord[Z] + obj->dir->coord[Z] * obj->height;
	if (hit_disk(ray, &cone_caps, hit))
		return (TRUE);
	return (FALSE);
}

_Bool	solve_quadratic_cone(
	double *coeff, double *roots, double *closest_hit)
{
	double	delta;
	// double	tmp;

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	// if (roots[0] < roots[1])
	// {
	// 	tmp = roots[0];
	// 	roots[0] = roots[1];
	// 	roots[1] = tmp;
	// }
	if (roots[0] > 0)
		*closest_hit = roots[0];
	else if (roots[1] > 0)
		*closest_hit = roots[1];
	else
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
	if (solve_quadratic_cone(coeff, roots, &ray->dist) && ray->dist > 0.05
		&& check_height(ray, obj))
	{
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit);
		return (TRUE);
	}
	if (hit_cone_caps(ray, obj, hit))
		return (TRUE);
	return (FALSE);
}
