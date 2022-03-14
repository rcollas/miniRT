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
	// check_direction_normal(ray, obj, hit);
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
	if (dot_origin < 0.0 || dot_height > 0.0)
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
	if (solve_quadratic_equation(coeff, roots, &ray->dist)
		&& check_height(ray, obj))
	{
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit, angle);
		return (TRUE);
	}
	if (hit_cone_caps(ray, obj, hit))
		return (TRUE);
	return (FALSE);
}
