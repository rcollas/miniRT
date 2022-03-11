#include "miniRT.h"

void	get_sphere_uv(t_ray hit, t_vec2 *uv)
{
	double	phi;
	double	theta;
	double	radius;
	double	raw_u;

	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	radius = get_norm_vec3(hit.dir);
	phi = acos(hit.dir.coord[Y] / radius);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	uv->coord[V] = 1 - phi / M_PI;
}

void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	raw_u;

	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	uv->coord[V] = hit.origin.coord[Z];
}

void	get_plane_uv(t_ray hit, t_vec2 *uv)
{
	uv->coord[U] = hit.origin.coord[X];
	uv->coord[V] = hit.origin.coord[Z];
}

t_vec2	transform_point_in_obj_space(
	t_vec3 hit_point, t_vec3 obj_origin, double max_dimension)
{
	t_vec2	new_point;

	new_point.coord[X] = hit_point.coord[X] - obj_origin.coord[X];
	new_point.coord[X] /= max_dimension;
	new_point.coord[Y] = hit_point.coord[Z] - obj_origin.coord[Z];
	new_point.coord[Y] /= max_dimension;
	return (new_point);
}

void	get_disk_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	radius;
	t_vec2	point;

	point = transform_point_in_obj_space(
			hit.origin, *hit.obj->origin, hit.obj->diameter / 2.0);
	radius = get_norm_vec2(point);
	theta = atan2(point.coord[Y], point.coord[X]);
	// uv->coord[U] = (radius - 0.25) / (0.5 - 0.25);
	uv->coord[U] = radius * 0.5 + 0.2;
	uv->coord[V] = theta * 0.5 / M_PI + 0.5;
	// printf("u = %f | v = %f\n", uv->coord[U], uv->coord[V]);
}
