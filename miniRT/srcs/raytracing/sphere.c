#include "miniRT.h"

_Bool	detect_intersection_with_sphere(t_ray *ray, double *coeff, t_ray *hit)
{
	double	delta;
	double	solution[2];

	delta = coeff[B] * coeff[B] - (4 * coeff[A] * coeff[C]);
	if (delta < 0)
		return (0);
	solution[0] = (-coeff[B] - (sqrt(delta))) / (2 * coeff[A]);
	solution[1] = (-coeff[B] + (sqrt(delta))) / (2 * coeff[A]);
	// printf("ret = %f\n", ret[1]);
	if (solution[1] < 0)
		return (FALSE);
	if (solution[0] > 0)
		ray->closest_hit = solution[0];
	else
		ray->closest_hit = solution[1];
	hit->origin = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->closest_hit));
	return (TRUE);
}

_Bool	hit_sphere(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	radius;

	radius = obj->diameter / 2;
	coeff[A] = 1;
	coeff[B] = 2 * dot_vec3(ray->dir, sub_vec3(ray->origin, *obj->origin));
	coeff[C] = get_norm2_vec3(sub_vec3(ray->origin, *obj->origin)) - radius * radius;
	if (detect_intersection_with_sphere(ray, coeff, hit))
	{
		hit->dir = get_normalized_vec3(sub_vec3(hit->origin, *obj->origin));
		return (TRUE);
	}
	return (FALSE);
}
