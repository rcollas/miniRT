#include "miniRT.h"

void	get_coeff(double coeff[3], t_ray *ray, t_obj *obj)
{
	t_vec3	cyl_to_origin;
	t_vec3	new_ray_dir;
	double	radius;

	normalize_vec3(obj->dir);
	radius = obj->diameter / 2;
	cyl_to_origin = sub_vec3(ray->origin, *obj->origin);
	new_ray_dir = cross_vec3(ray->dir, *obj->dir);
	coeff[A] = dot_vec3(new_ray_dir, new_ray_dir);
	coeff[B] = 2 * dot_vec3(
			new_ray_dir, cross_vec3(cyl_to_origin, *obj->dir));
	coeff[C] = dot_vec3(cross_vec3(cyl_to_origin, *obj->dir),
			cross_vec3(cyl_to_origin, *obj->dir));
	coeff[C] -= (radius * radius);
}

void	get_normal(t_ray *hit, t_ray *ray, t_obj *obj)
{
	t_vec3	new_origin;
	double	t;
	t_vec3	pt;
	t_vec3	bottom_origin;

	bottom_origin = sub_vec3(*obj->origin,
			mul_vec3_and_const(*obj->dir, obj->height / 2));
	new_origin = sub_vec3(hit->origin, bottom_origin);
	t = dot_vec3(*obj->dir, new_origin);
	pt = mul_vec3_and_const(*obj->dir, t);
	hit->dir = sub_vec3(new_origin, pt);
	normalize_vec3(&hit->dir);
	if (dot_vec3(hit->dir, ray->dir) > 0)
		hit->dir = mul_vec3_and_const(hit->dir, -1);
}

double	next_root(double *roots, double dist)
{
	if (roots[0] == dist)
		return (roots[1]);
	return (roots[0]);
}

double	in_cylinder_height(t_ray hit, t_obj obj)
{
	double	diagonal;
	double	radius;

	radius = obj.diameter / 2;
	diagonal = sqrt(4 * radius * radius + obj.height * obj.height) / 2;
	return (get_norm_vec3(sub_vec3(hit.origin, *obj.origin)) > diagonal
		|| hit.dist < 1e-4);
}

_Bool	hit_cylinder(t_ray *ray, t_obj *obj, t_ray *hit)
{
	double	coeff[3];
	double	roots[2];

	get_coeff(coeff, ray, obj);
	if (solve_quadratic_equation(coeff, roots, &ray->dist))
	{
		hit->origin = add_vec3(ray->origin,
				mul_vec3_and_const(ray->dir, ray->dist));
		hit->dist = ray->dist;
		get_normal(hit, ray, obj);
		if (in_cylinder_height(*hit, *obj))
		{
			ray->dist = next_root(roots, ray->dist);
			hit->origin = add_vec3(ray->origin,
					mul_vec3_and_const(ray->dir, ray->dist));
			hit->dist = ray->dist;
			get_normal(hit, ray, obj);
			if (in_cylinder_height(*hit, *obj))
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}
