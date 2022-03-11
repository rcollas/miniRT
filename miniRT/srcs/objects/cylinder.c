#include "miniRT.h"

#define O_CENTER 0
#define O_TOP 1
#define O_BOTTOM 2

void	get_coeff(double coeff[3], t_ray *ray, t_obj *obj)
{
	t_vec3	normalized_dir;
	t_vec3	cyl_to_origin;
	t_vec3	new_ray_dir;
	double	radius;

	radius = obj->diameter / 2;
//	normalized_dir = get_normalized_vec3(*obj->dir);
//	cyl_to_origin = sub_vec3(ray->origin, *obj->origin);
	normalized_dir = get_normalized_vec3(create_vec3(0, 1, 0));
	cyl_to_origin = sub_vec3(ray->origin, create_vec3(0, 0 ,-55));
	new_ray_dir = cross_vec3(ray->dir, normalized_dir);
	coeff[A] = dot_vec3(new_ray_dir, new_ray_dir);
	coeff[B] = 2 * dot_vec3(
			new_ray_dir, cross_vec3(cyl_to_origin, normalized_dir));
	coeff[C] = dot_vec3(cross_vec3(cyl_to_origin, normalized_dir),
			cross_vec3(cyl_to_origin, normalized_dir));
	coeff[C] -= (radius * radius);
}

void	set_origins(t_vec3 *cylinder, t_obj *obj)
{
//	cylinder[O_CENTER] = *obj->origin;
//	cylinder[O_TOP] = add_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height / 2));
//	cylinder[O_BOTTOM] = sub_vec3(*obj->origin, mul_vec3_and_const(*obj->dir, obj->height / 2));
	(void)cylinder;
	(void)obj;
	cylinder[O_CENTER] = create_vec3(0, 0, -55);
	cylinder[O_TOP] = add_vec3(cylinder[O_CENTER], mul_vec3_and_const(create_vec3(0, 1, 0), obj->height / 2));
	cylinder[O_BOTTOM] = sub_vec3(cylinder[O_CENTER], mul_vec3_and_const(cylinder[O_CENTER], obj->height / 2));
}

void	get_normal(t_ray *hit, t_ray *ray)
{
	t_vec3	new_origin;

	new_origin = create_vec3(0, 0, -55);
	new_origin.coord[Y] = hit->origin.coord[Y];
	hit->dir = sub_vec3(new_origin, hit->origin);
	if (dot_vec3(hit->dir, ray->dir) > 0)
		hit->dir = mul_vec3_and_const(hit->dir, -1);
	normalize_vec3(&hit->dir);

}

double	next_root(double *roots, double dist)
{
	if (roots[0] == dist)
		return (roots[1]);
	return (roots[0]);
}

double	distance_from_origin(t_vec3 hit, t_vec3 obj_origin)
{
	return (get_norm_vec3(sub_vec3(hit, obj_origin)));
}

_Bool	hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	roots[2];
	double	radius;
	t_vec3	cylinder[3];
	double	diagonale;

	set_origins(cylinder, obj);
	get_coeff(coeff, ray, obj);
	radius = obj->diameter / 2;
	diagonale = sqrt(4 * radius * radius + obj->height * obj->height) / 2;
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		get_normal(hit, ray);
		normalize_vec3(&hit->dir);
		if (distance_from_origin(hit->origin, cylinder[O_CENTER]) > diagonale)
		{
			ray->dist = next_root(roots, ray->dist);
			hit->origin = add_vec3(ray->origin, mul_vec3_and_const(ray->dir, ray->dist));
			hit->dist = ray->dist;
			get_normal(hit, ray);
			normalize_vec3(&hit->dir);
			if (distance_from_origin(hit->origin, cylinder[O_CENTER]) > diagonale)
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}
