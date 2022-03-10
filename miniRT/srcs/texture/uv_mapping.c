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

// void	get_disk_uv(t_ray hit, double *coord_uv)
// {
// 	coord_uv[U] = hit.origin.coord[X] * 0.5 + 0.5;
// 	coord_uv[V] = hit.origin.coord[Z] * 0.5 + 0.5;
// }

// void	get_disk_uv(t_ray hit, double *coord_uv)
// {
// 	double r = sqrt(hit.dir.coord[X] * hit.dir.coord[X]
// 		+ hit.dir.coord[Z] * hit.origin.coord[Z]);
// 	// coord_uv[V] = atan2(y / x);
// 	double theta = atan2(hit.dir.coord[Z], hit.dir.coord[X]);
// 	coord_uv[U] = r * cos(theta);
// 	coord_uv[V] = r * sin(theta);
// }

// void	get_disk_uv(t_ray hit, t_vec2 *uv)
// {
// 	double	r_inner;
// 	double	r_outer;
// 	double	angle;
// 	double	radius;
// 	t_vec3	centered_origin;

// 	(void)hit;
// 	r_inner = 0.25;
// 	r_outer = 0.5;
// 	centered_origin = get_normalized_vec3(hit.origin);
// 	// printf("x = %f | z = %f\n", centered_origin.coord[X], centered_origin.coord[Z]);
// 	angle = atan2(centered_origin.coord[Z], centered_origin.coord[X]);
// 	if (centered_origin.coord[X] < 0)
// 		angle += M_PI;
// 	else if (centered_origin.coord[X] > 0 && centered_origin.coord[Y] < 0)
// 		angle = angle + 2 * M_PI;
// 	radius =  sqrt(centered_origin.coord[X] * centered_origin.coord[X]
// 			+ centered_origin.coord[Z] * centered_origin.coord[Z]);
// 	uv->coord[U] = radius * cos(angle) * 0.5 + 0.5;
// 	uv->coord[V] = radius * sin(angle) * 0.5 + 0.5;
// 	norm_text_coord(uv);
// 	uv->coord[U] = uv->coord[U] - 0.5;
// 	uv->coord[V] = uv->coord[V] - 0.5;
// 	radius = sqrt(uv->coord[U] * uv->coord[U] + uv->coord[V] * uv->coord[V]);
// 	angle = atan2(uv->coord[V], uv->coord[U]);
// 	if (centered_origin.coord[X] < 0)
// 		angle += M_PI;
// 	else if (centered_origin.coord[X] > 0 && centered_origin.coord[Y] < 0)
// 		angle = angle + 2 * M_PI;
// 	uv->coord[U] = (radius - r_inner) / (r_outer - r_inner);
// 	uv->coord[V] = angle * 0.5 / M_PI + 0.5;
// 	printf("u = %f | v = %f\n", uv->coord[U], uv->coord[V]);
// }

// void	get_init_disk_uv(t_ray hit, t_vec2 *uv)
// {
// 	t_vec3	centered_origin;
// 	double	angle;
// 	double	radius;

// 	centered_origin = get_normalized_vec3(hit.origin);
// 	// printf("x = %f | z = %f\n", centered_origin.coord[X], centered_origin.coord[Z]);
// 	angle = atan2(centered_origin.coord[Z], centered_origin.coord[X]);
// 	if (centered_origin.coord[X] < 0)
// 		angle += M_PI;
// 	else if (centered_origin.coord[X] > 0 && centered_origin.coord[Y] < 0)
// 		angle = angle + 2 * M_PI;
// 	radius =  sqrt(centered_origin.coord[X] * centered_origin.coord[X]
// 			+ centered_origin.coord[Z] * centered_origin.coord[Z]);
// 	// uv->coord[U] = radius * cos(angle) * 0.5 + 0.5;
// 	// uv->coord[V] = radius * sin(angle) * 0.5 + 0.5;
// 	uv->coord[U] = radius;
// 	uv->coord[V] = angle * 0.5 / M_PI + 0.5;
// 	normalize_vec2(uv);
// }

// void	get_disk_uv(t_ray hit, t_vec2 *uv)
// {
// 	double	theta;
// 	double	radius;
// 	t_vec2	center;
// 	t_vec2	norm_uv;
// 	t_vec2	point;

// 	point.coord[X] = hit.origin.coord[X];
// 	point.coord[Y] = hit.origin.coord[Z];
// 	normalize_vec2(&point);
// 	// printf("x = %f | z = %f\n", point.coord[X], point.coord[Y]);
// 	center.coord[X] = hit.obj->texture->center.coord[X];
// 	center.coord[Y] = hit.obj->texture->center.coord[Y];
// 	normalize_vec2(&center);
// 	norm_uv.coord[X] = 2.0 * point.coord[X] - center.coord[X];
// 	norm_uv.coord[Y] = 2.0 * point.coord[Y] - center.coord[Y];
// 	radius = get_norm_vec2(norm_uv);
// 	theta = atan2(norm_uv.coord[Y], norm_uv.coord[X]);

// 	// if (radius > 0.0 && radius < 2.0)
// 	// 	radius = ceil(radius / 0.9) * 0.9;
// 	// if (theta > 0.0 && theta < 6.0)
// 	// 	theta = floor(theta / 0.8) * 0.8;
// 	radius = (radius < 0.0) ? radius : (radius > 0.0 + 2.0) ? radius : ceil(radius / 0.9) * 0.9;
//     theta = (theta < 0.0) ? theta : (theta > 0.0 + 5.0) ? theta : floor(theta / 0.8) * 0.8;

// 	norm_uv.coord[X] = radius * cos(theta);
// 	norm_uv.coord[Y] = radius * sin(theta);
// 	uv->coord[U] = norm_uv.coord[X] / 2.0 + (center.coord[X] / 2.0);
// 	uv->coord[V] = norm_uv.coord[Y] / 2.0 + (center.coord[Y] / 2.0);
// 	// printf("u = %f | v = %f\n", uv->coord[U], uv->coord[V]);
// }

t_vec2	transform_point_in_obj_space(t_vec3 hit_point, t_vec3 obj_origin, double max_dimension)
{
	t_vec2	new_point;

	new_point.coord[X] = (hit_point.coord[X] - obj_origin.coord[X]) / max_dimension;
	new_point.coord[Y] = (hit_point.coord[Z] - obj_origin.coord[Z]) / max_dimension;
	return (new_point);
}

void	get_disk_uv(t_ray hit, t_vec2 *uv)
{
	double	theta;
	double	radius;
	t_vec2	point;

	point = transform_point_in_obj_space(hit.origin, *hit.obj->origin, hit.obj->diameter / 2.0);
	// printf("x = %f | y = %f\n", point.coord[X], point.coord[Y]);
	radius = get_norm_vec2(point);
	// printf("radius = %f\n", radius);
	theta = atan2(point.coord[Y], point.coord[X]);
	uv->coord[U] = (radius - 0.25) / (0.5 - 0.25);
	uv->coord[V] = theta * 0.5 / M_PI + 0.5;
	// printf("u = %f | v = %f\n", uv->coord[U], uv->coord[V]);
}

// void	get_disk_uv(t_ray hit, t_vec2 *uv)
// {
// 	double	theta;
// 	double	radius;
// 	t_vec2	point;
// 	t_vec2	center;
// 	t_vec2	norm_point;

// 	point = transform_point_in_obj_space(hit.origin, hit.obj);
// 	// printf("x = %f | y = %f\n", point.coord[X], point.coord[Y]);
// 	// printf("radius = %f\n", radius);
// 	center.coord[X] = hit.obj->texture->center.coord[X];
// 	center.coord[Y] = hit.obj->texture->center.coord[Y];
// 	normalize_vec2(&center);
// 	norm_point.coord[X] = 2.0 * point.coord[X] - center.coord[X];
// 	norm_point.coord[Y] = 2.0 * point.coord[Y] - center.coord[Y];

// 	radius = get_norm_vec2(norm_point);
// 	theta = atan2(norm_point.coord[Y], norm_point.coord[X]);
// 	radius = (radius < 0.0) ? radius : (radius > 0.0 + 2.0) ? radius : ceil(radius / 1) * 1;
//     theta = (theta < 0.0) ? theta : (theta > 0.0 + 5.0) ? theta : floor(theta / 1) * 1;

// 	norm_point.coord[X] = radius * cos(theta);
// 	norm_point.coord[Y] = radius * sin(theta);
// 	uv->coord[U] = norm_point.coord[X] / 2.0 + (center.coord[X] / 2.0);
// 	uv->coord[V] = norm_point.coord[Y] / 2.0 + (center.coord[Y] / 2.0);
// 	printf("u = %f | v = %f\n", uv->coord[U], uv->coord[V]);
// }
