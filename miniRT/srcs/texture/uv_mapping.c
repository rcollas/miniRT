#include "miniRT.h"

void	get_sphere_uv(t_ray hit, double *coord_uv)
{
	double	phi;
	double	theta;
	double	radius;
	double	raw_u;

	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	radius = get_norm_vec3(hit.dir);
	phi = acos(hit.dir.coord[Y] / radius);
	raw_u = theta / (2 * M_PI);
	coord_uv[U] = 1 - (raw_u + 0.5);
	coord_uv[V] = 1 - phi / M_PI;
}

void	get_cylinder_uv(t_ray hit, double *coord_uv)
{
	double	theta;
	double	raw_u;

	theta = atan2(hit.dir.coord[X], hit.dir.coord[Z]);
	raw_u = theta / (2 * M_PI);
	coord_uv[U] = 1 - (raw_u + 0.5);
	coord_uv[V] = hit.origin.coord[Y];
}

void	get_plane_uv(t_ray hit, double *coord_uv)
{
	coord_uv[U] = hit.origin.coord[X];
	coord_uv[V] = hit.origin.coord[Z];
}

void	get_disk_uv(t_ray hit, double *coord_uv)
{
	coord_uv[U] = hit.origin.coord[X];
	coord_uv[V] = hit.origin.coord[Z];
}

// void	get_disk_uv(t_ray hit, double *coord_uv)
// {
// 	double r = sqrt(hit.dir.coord[X] * hit.dir.coord[X]
// 		+ hit.dir.coord[Z] * hit.origin.coord[Z]);
// 	// coord_uv[V] = atan2(y / x);
// 	double theta = atan2(hit.dir.coord[Z], hit.dir.coord[X]);
// 	coord_uv[U] = r * cos(theta);
// 	coord_uv[V] = r * sin(theta);
// }
