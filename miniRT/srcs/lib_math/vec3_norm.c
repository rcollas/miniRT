#include "miniRT.h"

double	get_norm_vec3(t_vec3 vector)
{
	double	norm;

	norm = sqrt(powf(vector.coord[X], 2) + powf(vector.coord[Y], 2) + powf(vector.coord[Z], 2));
	return (norm);
}

double	get_norm2_vec3(t_vec3 vector)
{
	double	norm;

	norm = powf(vector.coord[X], 2) + powf(vector.coord[Y], 2) + powf(vector.coord[Z], 2);
	return (norm);
}

void	normalize_vec3(t_vec3 *vector)
{
	double	norm_reciprocal;

	norm_reciprocal = 1 / get_norm_vec3(*vector);
	vector->coord[X] *= norm_reciprocal;
	vector->coord[Y] *= norm_reciprocal;
	vector->coord[Z] *= norm_reciprocal;
}

t_vec3	get_normalized_vec3(t_vec3 vector)
{
	normalize_vec3(&vector);
	return (vector);
}
