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

// void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
// {
// 	double	theta;
// 	double	raw_u;
// 	t_vec3	obj_dir;

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

void	from_world_to_tangent_space(t_ray *hit, t_vec3 new_hit_dir)
{
	t_vec3		tangent;
	t_vec3		bitangent;
	t_matrix4	tbn_matrix;

	normalize_vec3(&hit->dir);
	tangent = cross_vec3(hit->dir, create_vec3(0.0, 1.0, 0.0));
	if (!get_norm_vec3(tangent))
		tangent = cross_vec3(hit->dir, create_vec3(0.0, 0.0, 1.0));
	normalize_vec3(&tangent);
	bitangent = cross_vec3(tangent, hit->dir);
	normalize_vec3(&bitangent);
	tbn_matrix.row_1 = create_vec4(
			tangent.coord[X], bitangent.coord[X], hit->dir.coord[X], 0);
	tbn_matrix.row_2 = create_vec4(
			tangent.coord[Y], bitangent.coord[Y], hit->dir.coord[Y], 0);
	tbn_matrix.row_3 = create_vec4(
			tangent.coord[Z], bitangent.coord[Z], hit->dir.coord[Z], 0);
	tbn_matrix.row_4 = create_vec4(0, 0, 0, 1);
	tbn_matrix.row_1 = get_normalized_vec4(tbn_matrix.row_1);
	tbn_matrix.row_2 = get_normalized_vec4(tbn_matrix.row_2);
	tbn_matrix.row_3 = get_normalized_vec4(tbn_matrix.row_3);
	hit->dir = mul_vec3_and_matrix4(new_hit_dir, tbn_matrix);
}

void	get_cylinder_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	raw_u;

	from_world_to_tangent_space(&hit, hit.dir);
	normalize_vec3(&hit.dir);
	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	uv->coord[U] = 1 - (raw_u + 0.5);
	uv->coord[V] = hit.origin.coord[Y];
	// printf("u = %f   v = %f\n", uv->coord[U], uv->coord[V]);
}

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
