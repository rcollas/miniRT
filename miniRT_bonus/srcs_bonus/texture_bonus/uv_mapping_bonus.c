#include "miniRT_bonus.h"

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
	double		theta;
	double		raw_u;
	t_matrix3	rotation_matrix;

	normalize_vec3(&hit.dir);
	rotation_matrix = create_rotation_matrix(*hit.obj->dir);
	hit.dir = mul_dir_and_matrix3(hit.dir, rotation_matrix);
	hit.origin = mul_dir_and_matrix3(hit.origin, rotation_matrix);
	normalize_vec3(&hit.dir);
	// printf("%f  %f  %f\n", hit.dir.coord[X], hit.dir.coord[Y], hit.dir.coord[Z]);
	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	uv->coord[V] = hit.origin.coord[Y];
	// printf("u = %f   v = %f\n", uv->coord[U], uv->coord[V]);
}

// void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
// {
// 	double	theta;
// 	double	raw_u;
// 	t_vec3	obj_dir;
// 	double	diagonal;

// 	diagonal = sqrt(4 * obj.radius * obj.radius + obj.height * obj.height) / 2;
// 	copy_vec3(&obj_dir, *hit.obj->dir);
// 	normalize_vec3(&obj_dir);
// 	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
// 		theta = atan2(hit.dir.coord[Y], hit.dir.coord[Z]);
// 	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
// 		theta = atan2(hit.dir.coord[X], hit.dir.coord[Y]);
// 	else
// 		theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
// 	raw_u = theta / (2 * M_PI);
// 	uv->coord[U] = 1 - (raw_u + 0.5);
// 	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
// 		uv->coord[V] = hit.origin.coord[X];
// 	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
// 		uv->coord[V] = hit.origin.coord[Z];
// 	else
// 		uv->coord[V] = hit.origin.coord[Y];
// }

void	get_plane_uv(t_ray hit, t_vec2 *uv)
{
	t_vec3	obj_dir;

	copy_vec3(&obj_dir, *hit.obj->dir);
	if (obj_dir.coord[X] == 1 || obj_dir.coord[X] == -1)
	{
		uv->coord[U] = hit.origin.coord[Y];
		uv->coord[V] = hit.origin.coord[Z];
	}
	else if (obj_dir.coord[Z] == 1 || obj_dir.coord[Z] == -1)
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Y];
	}
	else
	{
		uv->coord[U] = hit.origin.coord[X];
		uv->coord[V] = hit.origin.coord[Z];
	}
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
