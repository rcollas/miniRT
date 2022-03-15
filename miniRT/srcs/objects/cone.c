#include "miniRT.h"

void	check_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	dot;
	t_vec3	rejection;

	(void)obj;
	// normalize_vec3(&ray->dir);
	// if (dot_vec3(hit->dir, ray->dir) > 0)
	if (dot_vec3(hit->dir, ray->dir) > 0.2)
	{
		dot = dot_vec3(hit->dir, *obj->dir) / dot_vec3(*obj->dir, *obj->dir);
		rejection = sub_vec3(hit->dir, mul_vec3_and_const(*obj->dir, dot));
		// hit->dir = sub_vec3(hit->dir, rejection);
		// hit->dir = sub_vec3(hit->dir, rejection);
		// printf("dot = %f\n", dot_vec3(hit->dir, ray->dir));
		// dot = dot_vec3(hit->dir, *obj->dir);
		// hit->dir = sub_vec3_and_const(hit->dir, 2 * dot);

		// printf("hit->dir : %f  %f  %f\n", hit->dir.coord[X], hit->dir.coord[Y], hit->dir.coord[Z]);
		hit->dir = mul_vec3_and_const(hit->dir, -1);
		// if (dot_vec3(hit->dir, ray->dir) > 0)
		// 	hit->dir = mul_vec3_and_const(hit->dir, -1);
		// if (BONUS && obj->type == SPHERE)
		// obj->inside_object = TRUE;
	}
}

void	compute_normal_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	length;

	(void)ray;
	length = get_norm_vec3(sub_vec3(hit->origin, *obj->origin));
	hit->dir = sub_vec3(hit->origin, add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, length)));
	normalize_vec3(&hit->dir);
	check_normal_cone(ray, obj, hit);
	normalize_vec3(&hit->dir);
}

_Bool	check_height(t_ray *ray, t_obj *obj, double ray_dist)
{
	t_vec3	vec_1;
	t_vec3	vec_2;
	double	dot_origin;
	double	dot_height;

	vec_1 = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray_dist));
	vec_2 = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height));
	dot_origin = dot_vec3(*obj->dir, sub_vec3(vec_1, *obj->origin));
	dot_height = dot_vec3(*obj->dir, sub_vec3(vec_1, vec_2));
	if (dot_origin < 0.001 || dot_height > 0.001)
		return (FALSE);
	return (TRUE);
}

void	copy_ray(t_ray *dest, t_ray src)
{
	copy_vec3(&dest->dir, src.dir);
	copy_vec3(&dest->origin, src.origin);
	copy_vec3(&dest->color, src.color);
	dest->dist = src.dist;
	dest->shadowing = src.shadowing;
	dest->obj = src.obj;
}

_Bool	hit_cone_caps(t_ray *ray, t_obj *obj, t_ray *hit)
{
	t_obj	cone_caps;
	t_ray	hit_caps;
	t_ray	ray_caps;

	cone_caps = *obj;
	copy_ray(&hit_caps, *hit);
	copy_ray(&ray_caps, *ray);
	cone_caps.origin->coord[X] = obj->origin->coord[X] + obj->dir->coord[X] * obj->height;
	cone_caps.origin->coord[Y] = obj->origin->coord[Y] + obj->dir->coord[Y] * obj->height;
	cone_caps.origin->coord[Z] = obj->origin->coord[Z] + obj->dir->coord[Z] * obj->height;
	if (hit_disk(&ray_caps, &cone_caps, &hit_caps) && ray_caps.dist > 0.01
		&& ray_caps.dist < ray->dist)
	{
		copy_ray(ray, ray_caps);
		copy_ray(hit, hit_caps);
		return (TRUE);
	}
	return (FALSE);
}

_Bool	hit_cone_caps2(t_ray *ray, t_obj *obj, t_ray *hit)
{
	t_obj	cone_caps;
	t_ray	hit_caps;
	t_ray	ray_caps;

	cone_caps = *obj;
	copy_ray(&hit_caps, *hit);
	copy_ray(&ray_caps, *ray);
	cone_caps.origin->coord[X] = obj->origin->coord[X] + obj->dir->coord[X] * obj->height;
	cone_caps.origin->coord[Y] = obj->origin->coord[Y] + obj->dir->coord[Y] * obj->height;
	cone_caps.origin->coord[Z] = obj->origin->coord[Z] + obj->dir->coord[Z] * obj->height;
	if (hit_disk(&ray_caps, &cone_caps, &hit_caps) && hit_caps.dist > 0.01 && ray_caps.dist < ray->dist)
		// && check_height(&ray_caps, &cone_caps, ray_caps.dist))
	{
		copy_ray(ray, ray_caps);
		copy_ray(hit, hit_caps);
		return (TRUE);
	}
	return (FALSE);
}

_Bool	solve_quadratic_cone(
	double *coeff, double *closest_hit, t_ray *ray, t_obj *obj)
{
	double	delta;
	double	roots[2];

	(void)ray;
	(void)obj;
	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (FALSE);
	roots[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	roots[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	if (roots[0] > 0 && check_height(ray, obj, roots[0]))
		*closest_hit = roots[0];
	else if (roots[1] > 0 && check_height(ray, obj, roots[1]))
		*closest_hit = roots[1];
	else
		return (FALSE);
	return (TRUE);
}

_Bool	hit_cone(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;
	t_vec3	obj_to_origin;
	double	angle;
	t_vec3	theta;
	double	s_d1;
	double	s_d2;

	theta = get_normalized_vec3(*obj->dir);
	normalize_vec3(obj->dir);
	normalize_vec3(&ray->dir);
	radius = obj->diameter * 0.5;
	angle = (radius * radius) / (obj->height * obj->height);
	obj_to_origin = sub_vec3(ray->origin, *obj->origin);
	s_d1 = dot_vec3(ray->dir, theta);
	s_d2 = dot_vec3(obj_to_origin, theta);
	coeff[A] = dot_vec3(ray->dir, ray->dir) - angle * s_d1 * s_d1 - s_d1 * s_d1;
	coeff[B] = 2 * (dot_vec3(ray->dir, obj_to_origin) - angle * s_d1 * s_d2 - s_d1 * s_d2);
	coeff[C] = dot_vec3(obj_to_origin, obj_to_origin) - angle * s_d2 * s_d2 - s_d2 * s_d2;
	if (solve_quadratic_cone(coeff, &ray->dist, ray, obj) && ray->dist > 0.05)
	{
		if (hit_cone_caps(ray, obj, hit))
			return (TRUE);
		hit->origin = get_hit_point(*ray);
		hit->dist = ray->dist;
		compute_normal_cone(ray, obj, hit);
		return (TRUE);
	}
	if (hit_cone_caps2(ray, obj, hit))
		return (TRUE);
	return (FALSE);
}
