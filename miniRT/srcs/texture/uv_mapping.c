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

void	get_square_uv(t_ray hit, t_vec2 *uv)
{
	t_vec2	point;
	double	diagonal;

	diagonal = sqrt(hit.obj->height * hit.obj->height
			+ hit.obj->height + hit.obj->height);
	point = transform_point_in_obj_space(
			hit.origin, *hit.obj->origin, diagonal * 0.5, *hit.obj->dir);
	uv->coord[U] = point.coord[X] * 0.5 + 0.5;
	uv->coord[V] = point.coord[Y] * 0.5 + 0.5;
	if (hit.obj->dir->coord[Z] == 1 || hit.obj->dir->coord[X] == -1
		|| hit.obj->dir->coord[Y] == 1 || hit.obj->dir->coord[Y] == -1)
		uv->coord[U] = 1 - uv->coord[U];
	if (hit.obj->dir->coord[Y] == 1)
		uv->coord[V] = 1 - uv->coord[V];
}

void	get_disk_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	radius;
	t_vec2	point;

	point = transform_point_in_obj_space(hit.origin, *hit.obj->origin,
			hit.obj->diameter / 2.0, *hit.obj->dir);
	radius = get_norm_vec2(point);
	theta = atan2(point.coord[Y], point.coord[X]);
	uv->coord[U] = radius * 0.5 + 0.2;
	uv->coord[V] = theta * 0.5 / M_PI + 0.5;
}
